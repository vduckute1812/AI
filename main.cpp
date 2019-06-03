#include <QApplication>
#include "BoardGameWnd.h"
#include "BoardController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BoardController* boardController = BoardController::GetInstance();
    BoardGameWnd* boardWnd = BoardGameWnd::GetInstance();
    boardWnd->SetController(boardController);
    boardWnd->show();

    return a.exec();
}
