#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include "BoardUI.h"

class BoardController
{
public:
    void InitGame();
    BoardController();

private:
    static BoardTiles createTableTiles();
    BoardUI*        m_boardGame;
};

#endif // BOARDCONTROLLER_H
