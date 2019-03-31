#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include "Singleton.h"
#include "BoardUI.h"

class Move;
class Piece;
class BoardController: public Singleton<BoardController>
{
public:
    void InitGame();
    void setBoard(Board*);
    void movePiece(Piece* piece, Move* move);

    void printCurrentBoard();
    void freeGame();

private:
    BoardUI*        m_boardGame;
};

#endif // BOARDCONTROLLER_H
