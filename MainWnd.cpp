#include <QDockWidget>
#include <QFileInfo>
#include <QApplication>
#include <QTreeWidget>
#include "MainWnd.h"
#include "BoardGameWnd.h"
#include "BoardController.h"
#include "MoveMng.h"
#include <QKeyEvent>

//Returns true if s1 is less than s2
struct StringLT
{
    bool operator()(QString s1, QString s2) const
    {
        return QString::compare(s1, s2);
    }
};

typedef std::map<QString , QIcon*, StringLT > IconNameMap;

MainWnd::MainWnd(QWidget *parent/* = nullptr*/) : QMainWindow (parent)
{

}

void MainWnd::Init()
{
    BoardController* boardController = BoardController::GetInstance();
    BoardGameWnd* boardWnd = BoardGameWnd::GetInstance();
    boardWnd->SetController(boardController);

    m_boardDock = CreateDock("Board Game", "", boardWnd);
    AppendDock(m_boardDock, Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea, Qt::LeftDockWidgetArea);

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

                fn = (QString("Resources/") + iconStr + QString("-disabled") + extensions[i]);
                if (QFileInfo(fn).exists())
                    icon->addFile(fn, QSize(), QIcon::Disabled);

                fn = (QString("Resources/")  + iconStr + QString("-active") + extensions[i]);
                if (QFileInfo(fn).exists())
                    icon->addFile(fn, QSize(), QIcon::Active);

                fn = (QString("Resources/")  + iconStr + QString("-selected") + extensions[i]);
                if (QFileInfo(iconStr).exists())
                    icon->addFile(fn, QSize(), QIcon::Selected);
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

