#include "Tile.h"
#include "Piece.h"
#include "BoardGameWnd.h"
#include "BoardController.h"
#include "PieceFactory.h"
#include "Rook.h"
#include "BoardUntils.h"
#include "HistoryWnd.h"
#include "MainWnd.h"
#include "MoveMgr.h"

#include "Player.h"

#include <QGridLayout>


BoardGameWnd::BoardGameWnd(BoardController* controller, QWidget* parent/* = nullptr*/)
    : QWidget(parent)
    , Messenger()
{
    m_boardController = controller;
}

BoardGameWnd::~BoardGameWnd()
{
    std::vector<Piece*>::iterator piecePtr;
    for (piecePtr = m_pieces.begin(); piecePtr != m_pieces.end(); ++piecePtr)
    {
        delete *piecePtr;
        *piecePtr = nullptr;
    }

    for (u32 i = 0; i < MAX_TEMP_BOARD; ++i)
    {
        m_tempBoards.pieceData.clear();
    }
    delete m_boardController;
}

void BoardGameWnd::CreateStandardBoard()
{
    u32 endBoardIdx = NUM_TILES_PER_ROW * NUM_TILES_PER_COL - 1;
    const QList<QString> listInit = {"Rook","Knight","Bishop","King","Queen","Bishop","Knight","Rook"
                                    ,"Pawn", "Pawn" ,"Pawn"  ,"Pawn","Pawn" , "Pawn" ,"Pawn"  ,"Pawn"};

    u32 sizeInit = static_cast<u32>(listInit.size());
    for(u32 i = 0; i < sizeInit; ++i)
    {
        Piece* piece_white = PieceFactory::GeneratePiece(listInit[int(i)], Alliance::BLACK);
        piece_white->SetPosition(i);
        m_tempBoards.pieceData.at(i) = piece_white;
        m_pieces.push_back(piece_white);

        Piece* piece_black = PieceFactory::GeneratePiece(listInit[int(i)], Alliance::WHITE);
        piece_black->SetPosition(endBoardIdx - i);
        m_tempBoards.pieceData.at(endBoardIdx - i) = piece_black;
        m_pieces.push_back(piece_black);
    }

    m_tempBoards.playerTurn = Alliance::WHITE;
}

MoveCollection BoardGameWnd::GetLegalMoves(BoardConfig board, Alliance player)
{
    MoveCollection moveCollections;
    PiecePositions::iterator piecePtr = board.pieceData.begin();

    for (;piecePtr!=board.pieceData.end();++piecePtr)
    {
        Piece* piece = *piecePtr;
        if(BoardUntils::IsSameAlliance(piece->GetAlliance(), player))
        {
            for(Move* move: piece->calculateLegalMove(board))
            {
                moveCollections.push_back(move);
            }
        }
    }
    return moveCollections;
}

BoardTiles BoardGameWnd::GetTiles()
{
    return m_tiles;
}

void BoardGameWnd::Init()
{
    Lock(true); // lock init for avoiding crash
    blockSignals(true);

    Piece* NULL_PIECE = nullptr;

    for (unsigned int i = 0; i < NUM_TILES; ++i)
    {
        Tile* tile = new Tile(i, NULL_PIECE);
        ListenTo(tile, k_msgType, msg::BOARD_CHANGED);
        tile->SetCanTouch(true);
        m_tiles.push_back(tile);
        m_tempBoards.pieceData.push_back( NULL_PIECE);
    }

    CreateStandardBoard();

    setMinimumSize(TILE_ROW_SIZE * NUM_TILES_PER_ROW,
                 TILE_COL_SIZE * NUM_TILES_PER_ROW);

    QGridLayout *gridLayout = new QGridLayout();

    // Set parrent and move tiles to their coordinate
    BoardTiles::iterator tilePtr;
    for (tilePtr = m_tiles.begin(); tilePtr != m_tiles.end(); ++tilePtr)
    {
        Tile* tile = *tilePtr;
        tile->setParent(this);
        gridLayout->addWidget(tile, tile->GetCoordinate() / NUM_TILES_PER_ROW, tile->GetCoordinate() % NUM_TILES_PER_ROW);
    }

    // Set piece on board
    PiecePositions::iterator piecePtr;
    for (piecePtr = m_tempBoards.pieceData.begin(); piecePtr != m_tempBoards.pieceData.end(); ++piecePtr)
    {
        Piece* piece = *piecePtr;
        if(piece != nullptr)
        {
            u32 location = piece->GetPosition();
            Tile* tile = m_tiles.at(location);

            tile->SetPiece(piece);
            piece->setParent(tile);
        }
    }

    gridLayout->setSpacing(0);
    setLayout(gridLayout);

    Lock(false);    //
    blockSignals(false);

    m_whitePlayer = new WhitePlayer();

    m_blackPlayer = new BlackPlayer();  // IS ai player
    m_blackPlayer->SetIsAI(true);

    m_currentPlayer = GetCurrentPlayer();

    ListenTo(MoveMgr::GetInstance(), BoardGameWnd::k_msgType, msg::BOARD_CHANGED);
}

void BoardGameWnd::SetController(BoardController *controller)
{
    m_boardController = controller;
}

void BoardGameWnd::SetBoard(BoardConfig board)
{
    Lock(true); // lock init for avoiding crash

    ResetColorTiles();

    m_tempBoards = board;
    ResetTiles();

    PiecePositions::iterator pieceConfig = m_tempBoards.pieceData.begin();

    for (; pieceConfig!=m_tempBoards.pieceData.end(); ++pieceConfig)
    {
        Piece* piece = *pieceConfig;
        if(piece)
        {
            const u32 coordinate = piece->GetPosition();
            m_tiles.at(coordinate)->SetPiece(piece);
        }
    }

    Lock(false);


}

void BoardGameWnd::ResetColorTiles()
{
    // Set parrent and move tiles to their coordinate
    BoardTiles::iterator tilePtr;
    for (tilePtr = m_tiles.begin(); tilePtr != m_tiles.end(); ++tilePtr)
    {
        Tile* tile = *tilePtr;
        tile->SetCurrentColor(tile->GetDefaultColor());
    }
}

void BoardGameWnd::LockTiles(bool yes)
{
    BoardTiles::iterator tilePtr;
    for (tilePtr = m_tiles.begin(); tilePtr != m_tiles.end(); ++tilePtr)
    {
        Tile* tile = *tilePtr;
        tile->SetCanTouch(yes);
    }
}

void BoardGameWnd::AddPieceOnBoard(Piece *piece)
{
    m_pieces.push_back(piece);
}

void BoardGameWnd::OnMessageReceived(const Message &msg)
{
//    if(msg.IsFrom<MainWnd>())   // receive message from MainWnd
//    {
        if(msg.Is(msg::MOVE))
        {
            // will do more in here
        }
        else if(msg.Is(msg::ATTACK))
        {
            // will do more in here
        }
        else if(msg.Is(msg::DEFEND))
        {
            // will do more in here
        }
        else if(msg.Is(msg::DEFEND))
        {
            // will do more in here
        }

        if(msg.Is(msg::BOARD_CHANGED))
        {
            repaint();
        }
//    }

}

//void BoardGameWnd::Update()
//{

//}

Player *BoardGameWnd::GetCurrentPlayer()
{
    return m_tempBoards.playerTurn == Alliance::WHITE ? m_whitePlayer : m_blackPlayer;
}


void BoardGameWnd::ResetTiles()
{
    BoardTiles::iterator tilePtr;
    for (tilePtr = m_tiles.begin(); tilePtr != m_tiles.end(); ++tilePtr)
    {
        Tile* tile = *tilePtr;
        tile->SetPiece(nullptr);
    }
}

