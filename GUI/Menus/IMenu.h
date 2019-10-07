#ifndef IMENU_H
#define IMENU_H

#include <QMainWindow>
//#include "GUI/MenuManager.h"

class IMenu
{
public:
    enum MenuType
    {
        k_LoginMenu,
        k_MainMenu,
        k_PlayGameMenu,
        k_ScoreMenu,
        k_OptionMenu
    };
public:
    IMenu(MenuType menuType, std::string menuName);
    virtual ~IMenu();

public:
    virtual void CreateMenu() = 0;
    virtual void Show() = 0;
    virtual void Destroy() = 0;

public:

    //setter
    void SetWND(QMainWindow* wnd) {m_menuWND = wnd;}

    //getter
    std::string GetMenuName() {return m_menuName;}

    //methods
    void ShowWND(){m_menuWND->show();}

private:
    MenuType m_type;
    QMainWindow* m_menuWND;
    std::string m_menuName;
};

#endif // IMENU_H
