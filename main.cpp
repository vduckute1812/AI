#include <QApplication>
#include "GUI/MainWnd.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWnd* mainWnd = MainWnd::GetInstance();
    mainWnd->Init();

    mainWnd->Show();

    return a.exec();
}
