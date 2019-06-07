#include "Tile.h"
#include "Piece.h"
#include "BoardGameWnd.h"
#include "BoardController.h"
#include "PieceFactory.h"

#include "Rook.h"

#include <QGridLayout>

BoardGameWnd::BoardGameWnd(BoardController* controller, QWidget* parent/* = nullptr*/)
    : QWidget(parent)
    , Messenger()
{
    m_boardController = controller;
    startTimer(50);
}

BoardGameWnd::~BoardGameWnd()
{
    delete m_boardController;
}

BoardState BoardGameWnd::CreateStandardBoard()
{
    BoardState stardardBoard;
    unsigned int endBoardIdx = NUM_TILES_PER_ROW * NUM_TILES_PER_COL - 1;
    const QList<QString> listInit = {"Rook","Knight","Bishop","King","Queen","Bishop","Knight","Rook"
                               ,"Pawn","Pawn"  ,"Pawn"  ,"Pawn","Pawn" , "Pawn" ,"Pawn"  ,"Pawn"};

    for(unsigned int i = 0; i < listInit.size(); ++i)
    {
        Piece* piece_white = PieceFactory::GeneratePiece(listInit[i], Alliance::BLACK);
        piece_white->SetPosition(i);
        stardardBoard.m_boardValue.push_back(std::make_pair(i, piece_white));

        Piece* piece_black = PieceFactory::GeneratePiece(listInit[i], Alliance::WHITE);
        piece_black->SetPosition(endBoardIdx - i);
        stardardBoard.m_boardValue.push_back(std::make_pair(endBoardIdx - i, piece_black));
    }

    stardardBoard.m_playerTurn = Alliance::WHITE;

    return stardardBoard;
}

BoardTiles BoardGameWnd::GetTiles()
{
    return m_tiles;
}

void BoardGameWnd::Init()
{
    m_isLocked = false;

    m_tiles = Tile::createEmptyTiles();
    BoardState initBoard = BoardGameWnd::CreateStandardBoard();

    SetBoard(initBoard);

    setMinimumSize(TILE_ROW_SIZE * NUM_TILES_PER_ROW,
                 TILE_COL_SIZE * NUM_TILES_PER_ROW);

    QGridLayout *gridLayout = new QGridLayout();

    // Set parrent and move tiles to their coordinate
    BoardTiles::iterator tilePtr;
    gridLayout->setSpacing(0);
    for (tilePtr = m_tiles.begin(); tilePtr != m_tiles.end(); ++tilePtr)
    {
        Tile* tile = *tilePtr;
        tile->setParent(this);
        gridLayout->addWidget(tile, tile->GetCoordinate() / NUM_TILES_PER_ROW, tile->GetCoordinate() % NUM_TILES_PER_ROW);
    }

    // Set piece on board
    BoardConfig::iterator piecePtr;
    for (piecePtr = m_boardState.m_boardValue.begin(); piecePtr != m_boardState.m_boardValue.end(); ++piecePtr)
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

    setLayout(gridLayout);

////    // Set default move maker
//    BoardController::GetInstance()->SetMoveMaker(Alliance::WHITE);
}

void BoardGameWnd::SetController(BoardController *controller)
{
    m_boardController = controller;
}

void BoardGameWnd::SetBoard(BoardState board)
{
    ResetColorTiles();

    if(!m_boardState.m_boardValue.empty())
    {
        m_boardState.m_boardValue.clear();
    }
    m_boardState = board;
    ResetTiles();
    BoardConfig config = m_boardState.m_boardValue;
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
