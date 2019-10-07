#include <QApplication>
#include "GUI/MenuComponents/GamePlayMenu/MainWnd.h"
#include "GUI/MenuFactory.h"
#include "GUI/MenuManager.h"
#include "Application.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Application::GetInstance()->Init();

    Application::GetInstance()->Update();

    return a.exec();
}
