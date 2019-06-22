#include "Tile.h"
#include "Piece.h"
#include "BoardGameWnd.h"
#include "BoardController.h"
#include "PieceFactory.h"
#include "Rook.h"
#include "BoardUntils.h"
#include "HistoryWnd.h"

#include <QGridLayout>


BoardGameWnd::BoardGameWnd(BoardController* controller, QWidget* parent/* = nullptr*/)
    : QWidget(parent)
    , Messenger()
{
    s_tmpStateIdx = 0;

    m_boardController = controller;
    m_timer = new QTimer(this);

    // update thread
    connect(m_timer, SIGNAL(timeout()), this, SLOT(Update()), Qt::QueuedConnection);
    m_timer->start(50);

    // main thread
    startTimer(20);
}

BoardGameWnd::~BoardGameWnd()
{
    std::vector<Piece*>::iterator piecePtr;
    for (piecePtr = s_pieces.begin(); piecePtr != s_pieces.end(); ++piecePtr)
    {
        delete *piecePtr;
    }

    for (u32 i = 0; i < MAX_TEMP_BOARD; ++i)
    {
        s_tempBoards[i].m_boardValue.clear();
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
        s_tempBoards[0].m_boardValue.at(i).second = piece_white;
        s_pieces.push_back(piece_white);

        Piece* piece_black = PieceFactory::GeneratePiece(listInit[int(i)], Alliance::WHITE);
        piece_black->SetPosition(endBoardIdx - i);
        s_tempBoards[0].m_boardValue.at(endBoardIdx - i).second = piece_black;
        s_pieces.push_back(piece_black);
    }

    s_tempBoards[0].m_playerTurn = Alliance::WHITE;

    s_tmpStateIdx++;
}

MoveCollection BoardGameWnd::GetLegalMoves(BoardState board, Alliance player)
{
    MoveCollection moveCollections;
    BoardConfig::iterator piecePtr = board.m_boardValue.begin();

    for (;piecePtr!=board.m_boardValue.end();++piecePtr)
    {
        if(BoardUntils::IsSameAlliance(piecePtr->second->GetAlliance(), player))
        {
            for(Move* move: piecePtr->second->calculateLegalMove(board))
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
        tile->SetCanTouch(true);
        m_tiles.push_back(tile);
    }

    for(u32 i = 0; i < MAX_TEMP_BOARD; ++i)
    {
        for (int tileIdx = 0; tileIdx < NUM_TILES_PER_ROW * NUM_TILES_PER_COL; ++tileIdx)
        {
            s_tempBoards[i].m_boardValue.push_back(std::make_pair(tileIdx, NULL_PIECE));
        }
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
    BoardConfig::iterator piecePtr;
    for (piecePtr = s_tempBoards[0].m_boardValue.begin(); piecePtr != s_tempBoards[0].m_boardValue.end(); ++piecePtr)
    {
        u32 location = piecePtr->first;
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

    Lock(false);    //
    blockSignals(false);
}

void BoardGameWnd::SetController(BoardController *controller)
{
    m_boardController = controller;
}

void BoardGameWnd::SetBoard(BoardState board)
{
    Lock(true); // lock init for avoiding crash

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
        const u32 coordinate = tileConfig->first;
        Piece* piece = tileConfig->second;
        m_tiles.at(coordinate)->SetPiece(piece);
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

void BoardGameWnd::Update()
{
    if(IsLocked())
        return;
    HistoryWnd::GetInstance()->Update();
}

