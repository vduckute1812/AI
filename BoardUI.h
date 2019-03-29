#ifndef BOARDUI_H
#define BOARDUI_H

#include "Tile.h"
#include "Singleton.h"

class Board;


static BoardTiles   BOARD_TILES;


class BoardUI: public Singleton<BoardUI>
{
public:
    void InitBoardGame();
private:
    Board*          m_board;
};

#endif // BOARDUI_H
