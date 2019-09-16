#ifndef SCOREMENU_H
#define SCOREMENU_H

#include "GUI/Menus/IMenu.h"

class ScoreMenu: public IMenu
{
public:
    ScoreMenu();
    virtual ~ScoreMenu() override;

public:
    virtual void CreateMenu() override;
};

#endif // SCOREMENU_H
