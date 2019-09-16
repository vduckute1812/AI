#include "MenuFactory.h"

void MenuFactory::Initialize()
{
    m_menuName =
        {
            std::pair<IMenu::MenuType, std::string>(IMenu::MenuType::k_MainMenu,"Main Menu"),
            std::pair<IMenu::MenuType, std::string>(IMenu::MenuType::k_LoginMenu,"Login Menu"),
            std::pair<IMenu::MenuType, std::string>(IMenu::MenuType::k_PlayGameMenu,"Play Game Menu"),
            std::pair<IMenu::MenuType, std::string>(IMenu::MenuType::k_OptionMenu,"Option Menu"),
            std::pair<IMenu::MenuType, std::string>(IMenu::MenuType::k_ScoreMenu,"Score Menu"),
        };
}

void MenuFactory::OpenMenu(IMenu::MenuType menuType)
{
    qInfo()<<"Open Menu: "<<GetMenuName(menuType).c_str();
}

//void MenuFactory::RegisterMenu(IMenu::MenuType menuType, IMenu menu)
//{

//}

std::string MenuFactory::GetMenuName(IMenu::MenuType menuType)
{
    auto result = m_menuName.find(menuType);
    return result->second;
}
