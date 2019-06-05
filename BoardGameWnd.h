#ifndef BOARDGAMEWND_H
#define BOARDGAMEWND_H
#include <QWidget>
#include "Piece.h"
#include "Defines.h"
#include "Messenger.h"
#include "Singleton.h"

class Board;
class BoardController;

#define WAIT_CURSOR \
QApplication::setOverrideCursor(Qt::WaitCursor)

#define NORMAL_CURSOR \
QApplication::restoreOverrideCursor()

#define HIDE_CURSOR \
QApplication::setOverrideCursor(Qt::BlankCursor)

#define SYNC \
while (MainWnd::GetInstance()->IsLocked()) \
Sleep(5)

class Tile;
class Piece;
typedef std::vector<Tile*> BoardTiles;

typedef std::vector<const Piece*> CollectPiece;

class BoardGameWnd : public QWidget, public Singleton<BoardGameWnd>, public Messenger
{
    Q_OBJECT

public:
    BoardGameWnd(BoardController* controller = nullptr, QWidget* parent = nullptr);
    ~BoardGameWnd();

    static BoardState       CreateStandardBoard();

    BoardTiles              GetTiles();

    struct EditModeDef
    {
        enum type
        {
            HUMAN_HUMAN,
            HUMAN_AI,
            AI_AI,
            COUNT
        };
    };

    virtual void            Init() override;

    void                    SetController(BoardController*);
    void                    SetBoard(BoardState board);
    const BoardState        GetCurrentBoard() {return m_boardState;}

    void                    ResetColorTiles();

    BoardController*        GetEditModeController() { return m_boardController; }

    bool					IsLocked() const { return m_isLocked; }
    void					Lock(bool yes) { m_isLocked = yes; }
    void                    timerEvent(QTimerEvent *e) override;

private:
    volatile bool			m_isLocked;

    std::vector<Piece*>     m_pieces;
    BoardState              m_boardState;
    BoardController*        m_boardController;

    BoardTiles              m_tiles;
};

#endif // BOARDGAMEWND_H
