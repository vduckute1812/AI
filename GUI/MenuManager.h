#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "Singleton.h"
#include "Defines.h"
#include "GUI/Menus/IMenu.h"
#include "GUI/MenuFactory.h"

class MenuManager : public Singleton<MenuManager>
{
public:
//    MenuManager();
    void Init();
    void Update();
    void Destroy();

    void PushMenu(IMenu::MenuType menuType);
    void PopMenu();

    void GoBackToMainMenu();

private:
    std::vector<IMenu*>* m_menuStack;
    IMenu* m_currentMenu;
};

#endif // MENUMANAGER_H
