#include "Tile.h"
#include "Piece.h"
#include "BoardGameWnd.h"
#include "BoardController.h"
#include "PieceFactory.h"

#include "Rook.h"

#include <QGridLayout>

unsigned int BoardGameWnd::s_tmpStateIdx = 0;
std::vector<Piece*> BoardGameWnd::s_pieces;
BoardState BoardGameWnd::s_tempBoards[MAX_TEMP_BOARD];


BoardGameWnd::BoardGameWnd(BoardController* controller, QWidget* parent/* = nullptr*/)
    : QWidget(parent)
    , Messenger()
{
    m_boardController = controller;
    startTimer(50);
}

BoardGameWnd::~BoardGameWnd()
{
    std::vector<Piece*>::iterator piecePtr;
    for (piecePtr = s_pieces.begin(); piecePtr != s_pieces.end(); ++piecePtr)
    {
        delete *piecePtr;
    }

    for (unsigned int i = 0; i < MAX_TEMP_BOARD; ++i)
    {
        s_tempBoards[i].m_boardValue.clear();
    }
    delete m_boardController;
}

BoardState BoardGameWnd::CreateStandardBoard()
{
    unsigned int endBoardIdx = NUM_TILES_PER_ROW * NUM_TILES_PER_COL - 1;
    const QList<QString> listInit = {"Rook","Knight","Bishop","King","Queen","Bishop","Knight","Rook"
                                    ,"Pawn", "Pawn" ,"Pawn"  ,"Pawn","Pawn" , "Pawn" ,"Pawn"  ,"Pawn"};

    unsigned int sizeInit = static_cast<unsigned int>(listInit.size());
    for(unsigned int i = 0; i < sizeInit; ++i)
    {
        Piece* piece_white = PieceFactory::GeneratePiece(listInit[i], Alliance::BLACK);
        piece_white->SetPosition(i);
        s_tempBoards[0].m_boardValue.at(i).second = piece_white;
        s_pieces.push_back(piece_white);

        Piece* piece_black = PieceFactory::GeneratePiece(listInit[i], Alliance::WHITE);
        piece_black->SetPosition(endBoardIdx - i);
        s_tempBoards[0].m_boardValue.at(endBoardIdx - i).second = piece_black;
        s_pieces.push_back(piece_black);
    }

    s_tempBoards[0].m_playerTurn = Alliance::WHITE;

    s_tmpStateIdx++;

    return s_tempBoards[0];
}

BoardTiles BoardGameWnd::GetTiles()
{
    return m_tiles;
}

void BoardGameWnd::Init()
{
    m_isLocked = false;

    m_tiles = Tile::createEmptyTiles();

    Piece* NULL_PIECE = nullptr;
    for(unsigned int i = 0; i < MAX_TEMP_BOARD; ++i)
    {
        for (int tileIdx = 0; tileIdx < NUM_TILES_PER_ROW * NUM_TILES_PER_COL; ++tileIdx)
        {
            s_tempBoards[i].m_boardValue.push_back(std::make_pair(tileIdx, NULL_PIECE));
        }
    }

    BoardGameWnd::CreateStandardBoard();

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
    BoardConfig::iterator piecePtr;
    for (piecePtr = s_tempBoards[0].m_boardValue.begin(); piecePtr != s_tempBoards[0].m_boardValue.end(); ++piecePtr)
    {
        unsigned int location = piecePtr->first;
        Tile* tile = m_tiles.at(location);
        Piece* piece = piecePtr->second;

        tile->SetPiece(piece);
        if(piece != nullptr)
        {
            piece->setParent(tile);
        }
    }

    gridLayout->setSpacing(0);
    setLayout(gridLayout);
}

void BoardGameWnd::SetController(BoardController *controller)
{
    m_boardController = controller;
}

void BoardGameWnd::SetBoard(BoardState board)
{
    ResetColorTiles();

    if(!s_tempBoards[0].m_boardValue.empty())
    {
        s_tempBoards[0].m_boardValue.clear();
    }
    s_tempBoards[0] = board;
    ResetTiles();
    BoardConfig config = s_tempBoards[0].m_boardValue;
    BoardConfig::iterator tileConfig;

    for (tileConfig = config.begin(); tileConfig!=config.end(); ++tileConfig)
    {
        const unsigned int coordinate = tileConfig->first;
        Piece* piece = tileConfig->second;
        m_tiles.at(coordinate)->SetPiece(piece);
    }
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

void BoardGameWnd::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    repaint();
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
