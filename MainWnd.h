#ifndef MAINWND_H
#define MAINWND_H

#include <QMainWindow>
#include "Messenger.h"
#include "Singleton.h"


class PromoteWnd;
class MainWnd: public QMainWindow, public Singleton<MainWnd>, public Messenger
{
    Q_OBJECT
public:
    enum TypeMessage
    {
        k_msgType		= 1 << 4
    };
    MainWnd(QWidget *parent = nullptr);

    static const QIcon&     LoadIcon(QString iconStr);
    static const QPixmap&   LoadPixmap(QString iconStr);

    virtual void    Init() override;
    void            keyPressEvent(QKeyEvent *event) override;

    QDockWidget*    CreateDock(const char* name, QString icon, QWidget* widget);
    void            AppendDock(QDockWidget* dock, Qt::DockWidgetAreas allowedAreas, Qt::DockWidgetArea area);

    void            Show();

    void            SendMessage(Message& message);
    void            DeleteMessage();

public slots:
    // This method forces update of all dependent windows (warning: not thread-safe)
    void            Update();
    void            Render();

private:
    QTimer*         m_updateTimer;
    QTimer*         m_renderTimer;

    QDockWidget*	m_boardDock;
    QDockWidget*    m_historyDock;
    QDockWidget*    m_deadPieceDock;

    PromoteWnd*     m_promoteWnd;
};

#endif // MAINWND_H
