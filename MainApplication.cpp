#include "MainApplication.h"
#include "BoardController.h"
#include <QToolBar>

MainApplication::MainApplication(QWidget* parent): QMainWindow (parent)
{
    QPixmap doPix(QString("Resources/")+QString("do.png"));
    QPixmap undoPix(QString("Resources/")+QString("undo.png"));


    BoardController* boardController = BoardController::GetInstance();
    boardController->InitGame();
    boardController->printCurrentBoard();

    QToolBar* toolbar = addToolBar("main Toolbar");
    QAction* doAction = toolbar->addAction(QIcon(doPix), "Do action");
    QAction* undoAction = toolbar->addAction(QIcon(undoPix), "Undo action");

//    connect(doAction, &QAction::triggered, this, BoardController::GetInstance()->unDo);
}

MainApplication::~MainApplication()
{
    BoardController* boardController = BoardController::GetInstance();
    boardController->freeGame();
}
