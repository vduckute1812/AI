#include <QApplication>
#include "GUI/MenuComponents/MainWnd.h"
#include "GUI/MenuFactory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWnd* mainWnd = MainWnd::GetInstance();
    MenuFactory::GetInstance()->Initialize();
    MenuFactory::GetInstance()->OpenMenu(IMenu::MenuType::k_PlayGameMenu);

    mainWnd->Init();
    mainWnd->Show();

    return a.exec();
}
