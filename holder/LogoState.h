#pragma once
#include "State.h"

class LogoState: public State
{
public:
	virtual void OnInit();
	virtual void OnUpdate(float deltaTime);
	virtual void OnRender(Graphics* graphics);
	virtual void OnExit();

	LogoState();
	~LogoState();
private:
	float m_scrollValue;
};

