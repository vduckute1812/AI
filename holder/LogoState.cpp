#include "StateMachine.h"
#include "Define.h"
#include "LogoState.h"
#include "PlayState.h"
#include "ResourceManager.h"


LogoState::LogoState()
{
}


LogoState::~LogoState()
{
}


void LogoState::OnInit()
{
	m_scrollValue = SCREEN_HEIGHT;
}

void LogoState::OnUpdate(float deltaTime)
{
	if (m_scrollValue >= SCREEN_HEIGHT / 4.0f)
	{
		m_scrollValue -= deltaTime * 100;
	}
	else
	{
		StateMachine::GetInstance()->SwitchState(new PlayState());
	}
}

void LogoState::OnRender(Graphics* graphics)
{
	graphics->DrawTextWithFont(ResourceManager::GetInstance()->GetFontById(1),
								SCREEN_WIDTH / 4.0f, m_scrollValue, "Hero Legends");

	graphics->DrawTextWithFont(ResourceManager::GetInstance()->GetFontById(0),
		SCREEN_WIDTH / 5.0f, m_scrollValue + 50, "Invasion Island");
}

void LogoState::OnExit()
{

}