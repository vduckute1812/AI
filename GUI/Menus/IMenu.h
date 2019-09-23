#ifndef IMENU_H
#define IMENU_H

#include <QMainWindow>

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
    IMenu(MenuType menuType);
    virtual ~IMenu();

public:
    virtual void CreateMenu() = 0;
    virtual void Show() = 0;
    virtual void Destroy() = 0;

public:
    void SetWND(QMainWindow* wnd) {m_menuWND = wnd;}
    void ShowWND(){m_menuWND->show();}
private:
    MenuType m_type;
    QMainWindow* m_menuWND;
};

#endif // IMENU_H
