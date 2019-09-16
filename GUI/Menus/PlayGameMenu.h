#ifndef PLAYGAMEMENU_H
#define PLAYGAMEMENU_H

#include "GUI/Menus/IMenu.h"

class PlayGameMenu: public IMenu
{
public:
    PlayGameMenu();
    virtual ~PlayGameMenu() override;

public:
    virtual void CreateMenu() override;
};

#endif // PLAYGAMEMENU_H
