#include "MoveMgr.h"
#include "MainApplication.h"
#include "BoardController.h"
#include "MoveMgr.h"
#include <QToolBar>
#include <QMenuBar>
#include <QDockWidget>

MainApplication::MainApplication(QWidget* parent): QMainWindow (parent)
{

}

MainApplication::~MainApplication()
{
    BoardController* boardController = BoardController::GetInstance();
    boardController->freeGame();
}

//void MainApplication::BuildMenus()
//{
//    menuBar()->clear();
//    //////////////////////////////////////////////////////////////////////////
//}

//void MainApplication::BuildToolMenus()
//{
//    delete m_undoToolbar;
//    m_undoToolbar = addToolBar("Undo");
//    m_undoToolbar->setObjectName("UndoToolbar");

//    m_undoAct = m_undoToolbar->addAction(QString("Resources/undo.png"), "Undo (Ctrl+Z)");
////    connect(m_undoAct, SIGNAL(triggered()), this, SLOT(UndoAct()));

//    m_redoAct = m_undoToolbar->addAction(QString("Resources/do.png"), "Redo (Ctrl+Y)");
////    connect(m_redoAct, SIGNAL(triggered()), this, SLOT(RedoAct()));
//}

//void MainApplication::UndoAct()
//{
//    MoveMgr::GetInstance()->Undo();
//}

//void MainApplication::RedoAct()
//{
//    MoveMgr::GetInstance()->Redo();
//}
