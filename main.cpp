#include <QCoreApplication>

#include "BoardController.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BoardController* boardController = BoardController::GetInstance();
    return a.exec();
}
