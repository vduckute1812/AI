#include "PlayState.h"
#include "ResourceManager.h"
#include "Define.h"

PlayState::PlayState()
{
}


PlayState::~PlayState()
{
}

void PlayState::OnInit()
{
	m_score = 0;
}

void PlayState::OnUpdate(float deltaTime)
{

}

void PlayState::OnRender(Graphics* graphics)
{
	graphics->DrawImage(ResourceManager::GetInstance()->GetImage(Background::MAP), 0, 0, 0);
	graphics->DrawImage(ResourceManager::GetInstance()->GetImage(Background::PlayerPut), 0, SCREEN_HEIGHT - BAR_HEIGHT, 0);
	graphics->DrawImage(ResourceManager::GetInstance()->GetImage(Background::AIPut), 0, 0, 0);

	graphics->DrawTextWithFont(ResourceManager::GetInstance()->GetFontById(1),
		0, 0, "Insance AI");

	graphics->DrawAnimation(ResourceManager::GetInstance()->GetAnimation(PlayerMode::AI, SizeCharacter::BIG), 0, 0, 0);
}

void PlayState::OnExit()
{

}