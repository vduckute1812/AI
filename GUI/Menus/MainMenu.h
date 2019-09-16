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
};

#endif // MAINMENU_H
