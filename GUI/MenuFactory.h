#ifndef MENUFACTORY_H
#define MENUFACTORY_H

#include <map>
#include "Singleton.h"
#include "Defines.h"
#include "GUI/Menus/IMenu.h"

class MenuFactory : public Singleton<MenuFactory>
{
public:
    void Initialize();
    void OpenMenu(IMenu::MenuType menuType);
//    void RegisterMenu(IMenu::MenuType menuType, IMenu menu);
    std::string GetMenuName(IMenu::MenuType menuType);

private:
    std::map <IMenu::MenuType, IMenu> m_menuMap;
    std::map <IMenu::MenuType, std::string> m_menuName;
};

#endif // MENUFACTORY_H
