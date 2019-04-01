#include "Tile.h"
#include "Piece.h"
#include "Board.h"
#include "BoardUI.h"
#include "BoardUntils.h"


void BoardUI::InitBoardGame()
{
    m_tiles = TILES::createEmptyTiles();
    Board* initBoard = BOARD::createStandardBoard();
    SetBoard(initBoard);

    setFixedSize(BoardUntils::TILE_ROW_SIZE * BoardUntils::NUM_TILES_PER_ROW,
                 BoardUntils::TILE_COL_SIZE * BoardUntils::NUM_TILES_PER_ROW);

    // Set parrent and move tiles to their coordinate
    BoardTiles::iterator tilePtr;
    for (tilePtr = m_tiles.begin(); tilePtr != m_tiles.end(); ++tilePtr)
    {
        Tile* tile = tilePtr->second;
        tile->setParent(this);
        tile->move(tile->getCoordinate() % BoardUntils::NUM_TILES_PER_ROW * BoardUntils::TILE_ROW_SIZE,
            tile->getCoordinate() / BoardUntils::NUM_TILES_PER_ROW * BoardUntils::TILE_COL_SIZE);
    }

    // Set piece on board
    BoardConfig boardConfig = m_board->getBoardConfig();
    BoardConfig::iterator piecePtr;
    for (piecePtr = boardConfig.begin(); piecePtr != boardConfig.end(); ++piecePtr)
    {
//        m_tiles.at(piecePtr->first)->setParent()
    }

    show();
    startTimer(50);
}

BoardTiles BoardUI::GetEmptyTiles()
{
    return m_tiles;
}

void BoardUI::ResetTiles()
{
    BoardTiles::iterator tilePtr;
    for (tilePtr = m_tiles.begin(); tilePtr != m_tiles.end(); ++tilePtr)
    {
        Tile* tile = tilePtr->second;
        tile->setPiece(nullptr);
    }
}

const Board* BoardUI::GetCurrentBoard()
{
    return m_board;
}

void BoardUI::SetBoard(Board *board)
{
    m_board = board;
    ResetTiles();
    BoardConfig config = m_board->getBoardConfig();
    BoardConfig::iterator tileConfig;

    for (tileConfig = config.begin(); tileConfig!=config.end(); ++tileConfig)
    {
        const int coordinate = tileConfig->first;
        Piece* piece = tileConfig->second;
        m_tiles.at(coordinate)->setPiece(piece);
    }
}

void BoardUI::FreeTiles()
{
    BoardTiles::iterator tilePtr;
    for (tilePtr = m_tiles.begin(); tilePtr != m_tiles.end(); ++tilePtr)
    {
        Tile* tileRelease = tilePtr->second;
        delete tileRelease;
    }
}

void BoardUI::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    repaint();
}
