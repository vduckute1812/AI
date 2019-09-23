#ifndef MAINMENU_H
#define MAINMENU_H

#include "GUI/Menus/IMenu.h"

class MainMenu : public IMenu
{
public:
    MainMenu();
    virtual ~MainMenu() override;

public:
    virtual void CreateMenu() override;
    virtual void Show() override;
    virtual void Destroy() override;
};

#endif // MAINMENU_H
