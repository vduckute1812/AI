#ifndef BOARDGAMEWND_H
#define BOARDGAMEWND_H
#include <QWidget>
#include <QTimer>
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
typedef std::vector<Piece*> CollectPieces;

class BoardGameWnd : public QWidget, public Singleton<BoardGameWnd>, public Messenger
{
    Q_OBJECT

public:
    BoardGameWnd(BoardController* controller = nullptr, QWidget* parent = nullptr);
    ~BoardGameWnd() override;

    BoardState&              CreateStandardBoard();

    static MoveCollection   GetLegalMoves(BoardState board, Alliance player);

    BoardTiles              GetTiles();

//    static std::vector<Piece*>      s_pieces;
//    static unsigned int             s_tmpStateIdx;
//    static BoardState               s_tempBoards[MAX_TEMP_BOARD];

    virtual void            Init() override;

    void                    SetController(BoardController*);
    void                    SetBoard(BoardState board);
    const BoardState        GetCurrentBoard() {return m_currentBoard;}

    void                    ResetColorTiles();

    BoardController*        GetEditModeController() { return m_boardController; }

    bool					IsLocked() const { return m_isLocked; }
    void					Lock(bool yes) { m_isLocked = yes; }
    void                    ResetTiles();
    void                    timerEvent(QTimerEvent *e) override;

public slots:
    // This method forces update of all dependent windows (warning: not thread-safe)
    void                    Update();

private:
    volatile bool			m_isLocked;
    BoardController*        m_boardController;
    BoardTiles              m_tiles;
    QTimer*                 m_timer;
    CollectPieces           m_pieces;
    BoardState              m_currentBoard;
};

#endif // BOARDGAMEWND_H
