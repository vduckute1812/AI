#ifndef MAINWND_H
#define MAINWND_H

#include <QMainWindow>
#include "Messenger.h"
#include "Singleton.h"


class PromoteWnd;
class MainWnd: public Singleton<MainWnd>, public QMainWindow, public Messenger
{

public:
    MainWnd(QWidget *parent = nullptr);

    static const QIcon&     LoadIcon(QString iconStr);
    static const QPixmap&   LoadPixmap(QString iconStr);

    virtual void    Init() override;
    void            keyPressEvent(QKeyEvent *event) override;

    QDockWidget*    CreateDock(const char* name, QString icon, QWidget* widget);
    void            AppendDock(QDockWidget* dock, Qt::DockWidgetAreas allowedAreas, Qt::DockWidgetArea area);


    void            Show();

private:
    QDockWidget*	m_boardDock;
    QDockWidget*    m_historyDock;
    QDockWidget*    m_deadPieceDock;

    PromoteWnd*     m_promoteWnd;
};

#endif // MAINWND_H
