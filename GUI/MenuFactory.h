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
//    void OpenMenu(IMenu::MenuType menuType);
    IMenu* GetMenu(IMenu::MenuType menuType);
    void RegisterMenu(IMenu::MenuType menuType, IMenu* menu);
    std::string GetMenuName(IMenu::MenuType menuType);

//    void InitializeMenuName();
    void InitializeMenuFactories();

private:
    std::map <IMenu::MenuType, IMenu*> m_menuFactories;
//    std::map <IMenu::MenuType, std::string> m_menuName;
};

#endif // MENUFACTORY_H
