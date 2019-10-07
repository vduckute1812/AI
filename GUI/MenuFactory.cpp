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
    RegisterMenu(new MainMenu());
    RegisterMenu(new LoginMenu());
    RegisterMenu(new PlayGameMenu());
    RegisterMenu(new OptionMenu());
    RegisterMenu(new ScoreMenu());
}

void MenuFactory::RegisterMenu(IMenu* menu)
{
    m_menuFactories.insert(std::pair<IMenu::MenuType, IMenu*>(menu->GetType(), menu));
}


