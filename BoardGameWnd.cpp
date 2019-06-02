#include "BoardGameWnd.h"
#include "BoardController.h"

BoardGameWnd::BoardGameWnd(BoardController* controller, QWidget* parent/* = nullptr*/)
    : QWidget(parent)
    , Messenger()
{
    m_boardController = controller;
}

BoardGameWnd::~BoardGameWnd()
{
    delete m_boardController;
}

void BoardGameWnd::Init()
{

}
