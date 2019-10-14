#pragma once
#include "State.h"

class PlayState: public State
{
public:
	virtual void OnInit();
	virtual void OnUpdate(float deltaTime);
	virtual void OnRender(Graphics* graphics);
	virtual void OnExit();
	PlayState();
	~PlayState();

private:
	int	m_score;
};

