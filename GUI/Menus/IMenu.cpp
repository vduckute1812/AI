#include "IMenu.h"

IMenu::IMenu(MenuType menuType, std::string menuName)
{
    this->m_type = menuType;
    this->m_menuName=menuName;
}

IMenu::~IMenu()
{

}


