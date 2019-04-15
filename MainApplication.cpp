#include "MoveMgr.h"
#include "MainApplication.h"
#include "BoardController.h"
#include <QToolBar>
#include <QDockWidget>

MainApplication::MainApplication(QWidget* parent): QMainWindow (parent)
{
    m_boardController = nullptr;
}

MainApplication::~MainApplication()
{
    BoardController* boardController = BoardController::GetInstance();
    boardController->freeGame();
}

bool MainApplication::isAIplayer() const
{
    return false;
}


void MainApplication::Init()
{
    m_boardController = BoardController::GetInstance();
    m_boardController->InitGame();
    m_boardController->printCurrentBoard();

//    QPixmap doPix(QString("Resources/")+QString("do.png"));
//    QPixmap undoPix(QString("Resources/")+QString("undo.png"));

//    QActionGroup* g = new QActionGroup(this);
//    connect(g, SIGNAL(triggered(QAction*)), this, SLOT(ActionGrp(QAction*)));

//    QToolBar* toolbar = addToolBar("main Toolbar");
//    QAction* redoAction = toolbar->addAction(QIcon(doPix), "Do action");
//    QAction* undoAction = toolbar->addAction(QIcon(undoPix), "Undo action");

//    connect(redoAction, SIGNAL(triggered()), this, SLOT(MoveMgr::Redo()), Qt::QueuedConnection);
//    connect(undoAction, SIGNAL(triggered()), this, SLOT(MoveMgr::Undo()), Qt::QueuedConnection);

//    QDockWidget* board = new QDockWidget(BoardUI::GetInstance());
//    setCentralWidget(board);
}

