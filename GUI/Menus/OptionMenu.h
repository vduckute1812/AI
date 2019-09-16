#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include "GUI/Menus/IMenu.h"

class OptionMenu: public IMenu
{
public:
    OptionMenu();
    virtual ~OptionMenu() override;

public:

    virtual void CreateMenu() override;
};

#endif // OPTIONMENU_H
