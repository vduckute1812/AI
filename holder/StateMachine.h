#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__
#include "State.h"
#include "ResourceManager.h"

class StateMachine
{
private:
	static StateMachine* instance;
	State* m_currentState;
	State* m_nextState;
	bool m_isExitCurrentState;
	bool m_isEnterNextState;
	StateMachine();
	~StateMachine();

public:
	static StateMachine* GetInstance();
	static void DestroyInstance();
	void Init(const char *path = "");
	void Update(float deltaTime);
	void Render(Graphics* graphics);
	void SwitchState(State *state);
	void TakeMousePosition(float x, float y, int mouseState);
	State* GetState();
};

#endif