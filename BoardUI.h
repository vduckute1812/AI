#ifndef BOARDUI_H
#define BOARDUI_H
#include <map>
#include <QWidget>
#include "Singleton.h"


class Board;
class Tile;

typedef std::map<int, Tile*> BoardTiles;

class BoardUI: public Singleton<BoardUI>, QWidget
{
public:
    void            InitBoardGame();
    BoardTiles      GetEmptyTiles();
    void            ResetTiles();

    void            SetBoard(Board* board);
    const Board*    GetCurrentBoard();
    void            FreeTiles();
    void            timerEvent(QTimerEvent *e) override;

private:
    Board*          m_board;
    BoardTiles      m_tiles;
};

#endif // BOARDUI_H
