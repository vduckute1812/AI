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
    virtual void Show() override;
    virtual void Destroy() override;
};

#endif // SCOREMENU_H
