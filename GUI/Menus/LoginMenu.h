#ifndef LOGINMENU_H
#define LOGINMENU_H

#include "GUI/Menus/IMenu.h"

class LoginMenu : public IMenu
{
public:
    LoginMenu();
    virtual ~LoginMenu() override;

public:

    virtual void CreateMenu() override;
};

#endif // LOGINMENU_H
