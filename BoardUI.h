#ifndef BOARDUI_H
#define BOARDUI_H
#include <map>
#include <QWidget>
#include "Singleton.h"


class Board;
class Tile;

typedef std::map<int, Tile*> BoardTiles;

class BoardUI: public Singleton<BoardUI>, public QWidget
{

public:
    ~BoardUI() override;

    void            InitBoardGame();
    BoardTiles      GetTiles();
    void            ResetTiles();

    void            SetBoard(Board* board);
    const Board*    GetCurrentBoard();
    void            FreeBoardGame();
    void            timerEvent(QTimerEvent *e) override;
    void            keyPressEvent(QKeyEvent *event) override;

    bool            IsLocked() const { return m_isLocked; }
    void            Lock(bool yes) { m_isLocked = yes; }

private:
    Board*          m_board;    //current Board
    BoardTiles      m_tiles;

    Board*          m_standardBoard;

    volatile bool				m_isLocked;
};

#endif // BOARDUI_H
