#include <QtWidgets/QApplication>

#include "BoardController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BoardController* boardController = BoardController::GetInstance();

    boardController->InitGame();

    boardController->printCurrentBoard();

//    boardController->FreeInstance();

    return a.exec();
}
