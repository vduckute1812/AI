#ifndef PLAYGAMEMENU_H
#define PLAYGAMEMENU_H

#include "GUI/Menus/IMenu.h"
#include "GUI/MenuComponents/GamePlayMenu/MainWnd.h"

class PlayGameMenu: public IMenu
{
public:
    PlayGameMenu();
    virtual ~PlayGameMenu() override;

public:
    virtual void CreateMenu() override;
    virtual void Show() override;
    virtual void Destroy() override;
};

#endif // PLAYGAMEMENU_H
