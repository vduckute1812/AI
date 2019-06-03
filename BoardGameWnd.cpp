#include "Tile.h"
#include "BoardGameWnd.h"
#include "BoardController.h"

#include <QGridLayout>

BoardGameWnd::BoardGameWnd(BoardController* controller, QWidget* parent/* = nullptr*/)
    : QWidget(parent)
    , Messenger()
{
    m_boardController = controller;
}

BoardGameWnd::~BoardGameWnd()
{
    delete m_boardController;
}

Board *BoardGameWnd::CreateStandardBoard()
{
    return nullptr;
}

void BoardGameWnd::Init()
{
    m_isLocked = false;

    m_tiles = Tile::createEmptyTiles();
    Board* initBoard = BoardGameWnd::CreateStandardBoard();
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

//    // Set piece on board
//    BoardConfig boardConfig = m_board->getBoardConfig();
//    BoardConfig::iterator piecePtr;
//    for (piecePtr = boardConfig.begin(); piecePtr != boardConfig.end(); ++piecePtr)
//    {
//        const int location = piecePtr->first;
//        Tile* tile = m_tiles.at(location);
//        Piece* piece = boardConfig.at(location);
//        if(piece != nullptr)
//            piece->setParent(tile);
//    }

    setLayout(gridLayout);
//    // Set move maker
    //    BoardController::GetInstance()->setMoveMaker(Alliance::WHITE);
}

void BoardGameWnd::SetController(BoardController *controller)
{
    m_boardController = controller;
}

void BoardGameWnd::SetBoard(Board *board)
{
    m_boardState = board;
}

void BoardGameWnd::SetBoardState(Board *board)
{
    m_boardState = board;
}
