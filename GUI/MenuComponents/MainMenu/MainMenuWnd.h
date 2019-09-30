#ifndef MAINMENUWND_H
#define MAINMENUWND_H

#include <QMainWindow>
#include <QSplitter>
#include "Singleton.h"
#include "Messenger.h"


class MainMenuWnd:
        public QMainWindow, public Singleton<MainMenuWnd>, public Messenger
{
public:
    virtual void    Init() override;
    void            keyPressEvent(QKeyEvent *event) override;

    void Show();
};

#endif // MAINMENUWND_H
