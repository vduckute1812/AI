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
    virtual void Show() override;
    virtual void Destroy() override;
};

#endif // OPTIONMENU_H
