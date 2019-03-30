#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include "Singleton.h"
#include "BoardUI.h"

class BoardController: public Singleton<BoardController>
{
public:
    void InitGame();
    void setBoard(Board*);

private:
    BoardUI*        m_boardGame;
};

#endif // BOARDCONTROLLER_H
