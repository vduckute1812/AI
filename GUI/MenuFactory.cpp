#include "MenuFactory.h"

void MenuFactory::Initialize()
{
    InitializeMenuName();
    InitializeMenuFactories();
}

IMenu *MenuFactory::GetMenu(IMenu::MenuType menuType)
{
    IMenu* menu = m_menuFactories.find(menuType)->second;
    if  (menu!=nullptr)
    {
        return menu;
    }
}

void MenuFactory::InitializeMenuName()
{
    m_menuName.clear();
    m_menuName.insert(std::pair<IMenu::MenuType, std::string>(IMenu::MenuType::k_MainMenu,"Main Menu"));
    m_menuName.insert(std::pair<IMenu::MenuType, std::string>(IMenu::MenuType::k_LoginMenu,"Login Menu"));
    m_menuName.insert(std::pair<IMenu::MenuType, std::string>(IMenu::MenuType::k_PlayGameMenu,"Play Game Menu"));
    m_menuName.insert(std::pair<IMenu::MenuType, std::string>(IMenu::MenuType::k_OptionMenu,"Option Menu"));
    m_menuName.insert(std::pair<IMenu::MenuType, std::string>(IMenu::MenuType::k_ScoreMenu,"Score Menu"));
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

//void MenuFactory::OpenMenu(IMenu::MenuType menuType)
//{
//    qInfo()<<"Open Menu: "<<GetMenuName(menuType).c_str();
//}

std::string MenuFactory::GetMenuName(IMenu::MenuType menuType)
{
    auto result = m_menuName.find(menuType);
    return result->second;
}
