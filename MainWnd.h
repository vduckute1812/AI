#ifndef MAINWND_H
#define MAINWND_H

#include <QMainWindow>
#include "Messenger.h"
#include "Singleton.h"

class BoardGameWnd;
class MainWnd: public Singleton<MainWnd>, public QMainWindow, public Messenger
{
//    Q_OBJECT
public:
    MainWnd(QWidget *parent = nullptr);

    virtual void    Init() override;
    void            keyPressEvent(QKeyEvent *event) override;

    QDockWidget*    CreateDock(const char* name, QString icon, QWidget* widget);
    void            AppendDock(QDockWidget* dock, Qt::DockWidgetAreas allowedAreas, Qt::DockWidgetArea area);

    const QIcon&    LoadIcon(QString iconStr);

    void            Show();

private:
    QDockWidget*	m_boardDock;
};

#endif // MAINWND_H
