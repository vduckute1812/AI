#include <QDockWidget>
#include <QFileInfo>
#include <QApplication>
#include <QTreeWidget>
#include "MoveMgr.h"
#include "MainWnd.h"
#include "HistoryWnd.h"
#include "BoardGameWnd.h"
#include "DeadPieceWnd.h"
#include "PromoteWnd.h"
#include "BoardController.h"
#include "MainWnd.h"

#include <QKeyEvent>


typedef std::map<QString , QIcon*, StringLT > IconNameMap;

MainWnd::MainWnd(QWidget *parent/* = nullptr*/) : QMainWindow (parent)
{
    m_updateTimer = new QTimer(this);
    // update thread
    connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(Update()), Qt::QueuedConnection);
    m_updateTimer->start(50);
}

void MainWnd::Init()
{
    BoardController* boardController = new BoardController();
    BoardGameWnd* boardWnd = BoardGameWnd::GetInstance();
    boardWnd->Init();
    boardWnd->SetController( boardController);

    HistoryWnd* historyWnd = HistoryWnd::GetInstance();
    historyWnd->Init();
    m_historyDock = CreateDock("History", "history", historyWnd);
    m_historyDock->show();
    AppendDock(m_historyDock, Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea, Qt::RightDockWidgetArea);


    DeadPieceWnd* deadPieceWnd = DeadPieceWnd::GetInstance();
    deadPieceWnd->Init();
    m_deadPieceDock = CreateDock("Dead Piece", "dead", deadPieceWnd);
    m_deadPieceDock->show();
    AppendDock(m_deadPieceDock, Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea, Qt::LeftDockWidgetArea);

    m_promoteWnd = new PromoteWnd(this);
    m_promoteWnd->Init();
    m_promoteWnd->resize(600,300);
    m_promoteWnd->hide();

    m_boardDock = CreateDock("Board Game", "", boardWnd);
    setCentralWidget(boardWnd);
}

void MainWnd::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key::Key_Left)
    {
        MoveMgr::GetInstance()->Undo();
    }
    else if (event->key() == Qt::Key::Key_Right)
    {
        MoveMgr::GetInstance()->Redo();
    }
}

QDockWidget* MainWnd::CreateDock(const char *name, QString iconStr, QWidget *widget)
{
    QString qName(name);

    QDockWidget* dock = new QDockWidget(QString(qName), this);
    dock->hide(); // Hide it right away so it doesn't affect space distribution of dock area.
    dock->setObjectName(qName + " dock");
    dock->setWidget(widget);
    widget->setParent(dock);

    if (!iconStr.isEmpty())
    {
        dock->setWindowIcon(LoadIcon(QString(iconStr)));
    }
    return dock;
}

void MainWnd::AppendDock(QDockWidget *dock, Qt::DockWidgetAreas allowedAreas, Qt::DockWidgetArea area)
{
    dock->setAllowedAreas(allowedAreas);
    addDockWidget(area, dock);
}

const QIcon& MainWnd::LoadIcon(QString iconStr)
{
    const QList<QString> extensions = { ".svg", ".png", ".tga", ".ico", ".bmp" };

    QIcon* icon = nullptr;

    if(!iconStr.isEmpty())
    {
        for (int i = 0; i < static_cast<int>(extensions.size()); ++i)
        {
            QString fn(QString("Resources/") + iconStr + extensions[i]);

            QFileInfo info(fn);
            if (info.exists())
            {
                icon = new QIcon(fn);
                break;
            }
        }
    }

    return *icon;
}

const QPixmap &MainWnd::LoadPixmap(QString iconStr)
{
    const QList<QString> extensions = { ".svg", ".png", ".tga", ".ico", ".bmp" };

    QPixmap* icon = nullptr;

    if(!iconStr.isEmpty())
    {
        for (int i = 0; i < static_cast<int>(extensions.size()); ++i)
        {
            QString fn(QString("Resources/") + iconStr + extensions[i]);

            QFileInfo info(fn);
            if (info.exists())
            {
                icon = new QPixmap(fn);
                break;
            }
        }
    }

    return *icon;
}

void MainWnd::Show()
{
    show();
    QApplication::processEvents(); // Make sure it is all processed before state restoration.
}



void MainWnd::Update()
{
    if(BoardGameWnd::GetInstance()->IsLocked())
        return;
    HistoryWnd::GetInstance()->Update();
    BoardGameWnd::GetInstance()->Update();
}
