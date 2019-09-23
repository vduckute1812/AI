#include "MenuManager.h"

void MenuManager::Init()
{
    m_menuStack = new std::vector<IMenu*>();
    MenuFactory::GetInstance()->Initialize();
//    this->GetInstance()->PushMenu(IMenu::MenuType::k_PlayGameMenu);
}

void MenuManager::Update()
{
    m_currentMenu->Show();
}

void MenuManager::PushMenu(IMenu::MenuType menuType)
{
    m_currentMenu = MenuFactory::GetInstance()->GetMenu(menuType);
    if (m_currentMenu!=nullptr)
    {
        m_menuStack->push_back(m_currentMenu);
    }
}

void MenuManager::PopMenu()
{
    m_menuStack->pop_back();
    m_currentMenu=m_menuStack->back();
}

void MenuManager::GoBackToMainMenu()
{
    m_menuStack->clear();
    m_currentMenu=MenuFactory::GetInstance()->GetMenu(IMenu::MenuType::k_MainMenu);
    m_menuStack->push_back(m_currentMenu);
}
