#include <QtWidgets/QApplication>
#include "BoardController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BoardController* boardController = BoardController::GetInstance();
    boardController->InitGame();
    boardController->printCurrentBoard();

    BoardUI::GetInstance()->show();

    return a.exec();
}
