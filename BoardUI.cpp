#include "Tile.h"
#include "Piece.h"
#include "Board.h"
#include "BoardUI.h"

void BoardUI::InitBoardGame()
{
    m_board = BOARD::createStandardBoard();
    m_tiles = TILES::createEmptyTiles();
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

Board* BoardUI::GetCurrentBoard()
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
