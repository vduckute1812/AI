#include "Application.h"


void Application::Init()
{
    MenuManager::GetInstance()->Init();
    MenuManager::GetInstance()->PushMenu(IMenu::MenuType::k_PlayGameMenu);
}

void Application::Update()
{
    MenuManager::GetInstance()->Update();
}

void Application::Destroy()
{

}
