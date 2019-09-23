#include <QApplication>
#include "GUI/MenuComponents/MainWnd.h"
#include "GUI/MenuFactory.h"
#include "GUI/MenuManager.h"
#include "Application.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    MainWnd* mainWnd = MainWnd::GetInstance();
//    MenuManager::GetInstance()->Init();

//    mainWnd->Init();
//    mainWnd->Show();

    Application::GetInstance()->Init();

    Application::GetInstance()->Update();

    return a.exec();
}
