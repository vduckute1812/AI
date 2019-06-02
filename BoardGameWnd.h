#ifndef BOARDGAMEWND_H
#define BOARDGAMEWND_H
#include <QWidget>

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

class BoardGameWnd : public QWidget, public Singleton<BoardGameWnd>, public Messenger
{
    Q_OBJECT

public:
    BoardGameWnd(BoardController* controller = nullptr, QWidget* parent = nullptr);
    ~BoardGameWnd();

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

    virtual void            Init();

    BoardController*        GetEditModeController() { return m_boardController; }


    bool					IsLocked() const { return m_isLocked; }
    void					Lock(bool yes) { m_isLocked = yes; }

private:
    volatile bool			m_isLocked;

    Board*                  m_boardState;
    BoardController*        m_boardController;
};

#endif // BOARDGAMEWND_H
