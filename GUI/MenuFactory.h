#ifndef MENUFACTORY_H
#define MENUFACTORY_H

#include "Singleton.h"
#include "Defines.h"

#include "GUI/Menus/IMenu.h"
#include "GUI/Menus/LoginMenu.h"
#include "GUI/Menus/MainMenu.h"
#include "GUI/Menus/OptionMenu.h"
#include "GUI/Menus/PlayGameMenu.h"
#include "GUI/Menus/ScoreMenu.h"

class MenuFactory : public Singleton<MenuFactory>
{
public:
    void Initialize();
    void RegisterMenu(IMenu* menu);

    IMenu* GetMenu(IMenu::MenuType menuType);
    std::string GetMenuName(IMenu::MenuType menuType);

    void InitializeMenuFactories();

private:
    std::map <IMenu::MenuType, IMenu*> m_menuFactories;
};

#endif // MENUFACTORY_H
