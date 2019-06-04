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
}

BoardGameWnd::~BoardGameWnd()
{
    delete m_boardController;
}

BoardConfig BoardGameWnd::CreateStandardBoard()
{
    BoardConfig stardardBoard;
    int endBoardIdx = NUM_TILES_PER_ROW * NUM_TILES_PER_COL - 1;
    const QList<QString> listInit = {"Rook","Knight","Bishop","King","Queen","Bishop","Knight","Rook"
                               ,"Pawn","Pawn"  ,"Pawn"  ,"Pawn","Pawn" , "Pawn" ,"Pawn"  ,"Pawn"};

    for(int i = 0; i < listInit.size(); ++i)
    {
        Piece* piece_white = PieceFactory::GeneratePiece(listInit[i], Alliance::WHITE);
        stardardBoard.push_back(std::make_pair(i, piece_white));

        Piece* piece_black = PieceFactory::GeneratePiece(listInit[i], Alliance::BLACK);
        stardardBoard.push_back(std::make_pair(endBoardIdx - i, piece_black));
    }


    return stardardBoard;
}

bool BoardGameWnd::IsTileOccupied( BoardConfig board, unsigned int position)
{
    BoardConfig::iterator piecePtr;
    for (piecePtr = board.begin(); piecePtr != board.end(); ++piecePtr)
    {
        if(piecePtr->first == position)
            return true;
    }
    return false;
}

Piece *BoardGameWnd::GetPieceOnBoard(BoardConfig board,  unsigned int position)
{
    BoardConfig::iterator piecePtr;
    for (piecePtr = board.begin(); piecePtr != board.end(); ++piecePtr)
    {
        if(piecePtr->first == position)
            return piecePtr->second;
    }
    return nullptr;
}

void BoardGameWnd::Init()
{
    m_isLocked = false;

    m_tiles = Tile::createEmptyTiles();
    BoardConfig initBoard = BoardGameWnd::CreateStandardBoard();
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
    for (piecePtr = m_boardState.begin(); piecePtr != m_boardState.end(); ++piecePtr)
    {
        unsigned int location = piecePtr->first;
        Tile* tile = m_tiles.at(location);
        Piece* piece = piecePtr->second;
        if(piece != nullptr)
            piece->setParent(tile);
    }

    setLayout(gridLayout);

//    // Set default move maker
//    BoardController::GetInstance()->setMoveMaker(Alliance::WHITE);
}

void BoardGameWnd::SetController(BoardController *controller)
{
    m_boardController = controller;
}

void BoardGameWnd::SetBoard(BoardConfig board)
{
    m_boardState = board;
}
