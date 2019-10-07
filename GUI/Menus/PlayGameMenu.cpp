#include "PlayGameMenu.h"

PlayGameMenu::PlayGameMenu()
    :IMenu (k_PlayGameMenu, "Play Game Menu")
{
//    this->SetWND(MainWnd::GetInstance());
    MainWnd::GetInstance()->Init();
}

PlayGameMenu::~PlayGameMenu()
{

}

void PlayGameMenu::CreateMenu()
{

}

void PlayGameMenu::Show()
{
    MainWnd::GetInstance()->Show();
}

void PlayGameMenu::Destroy()
{

}
