#include "MenuFactory.h"

void MenuFactory::Initialize()
{
    InitializeMenuFactories();
}

IMenu *MenuFactory::GetMenu(IMenu::MenuType menuType)
{
    IMenu* menu = m_menuFactories.find(menuType)->second;
    if  (menu!=nullptr)
    {
        return menu;
    }
    return nullptr;
}

std::string MenuFactory::GetMenuName(IMenu::MenuType menuType)
{

    auto result = m_menuFactories.find(menuType);
    return result->second->GetMenuName();
}

void MenuFactory::InitializeMenuFactories()
{
    m_menuFactories.clear();
    RegisterMenu(IMenu::MenuType::k_MainMenu,new MainMenu());
    RegisterMenu(IMenu::MenuType::k_LoginMenu,new LoginMenu());
    RegisterMenu(IMenu::MenuType::k_PlayGameMenu,new PlayGameMenu());
    RegisterMenu(IMenu::MenuType::k_OptionMenu,new OptionMenu());
    RegisterMenu(IMenu::MenuType::k_ScoreMenu,new ScoreMenu());
}

void MenuFactory::RegisterMenu(IMenu::MenuType menuType, IMenu* menu)
{
    m_menuFactories.insert(std::pair<IMenu::MenuType, IMenu*>(menuType, menu));
}


