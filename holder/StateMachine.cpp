#include "StateMachine.h"
#include "LogoState.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
	instance = 0;
	ResourceManager::GetInstance()->FreeInstance();
	delete m_currentState;
}

StateMachine* StateMachine::instance = 0; 

StateMachine* StateMachine::GetInstance()
{
	if (!instance)
	{
		instance = new StateMachine();
	}
	return instance;
}

void StateMachine::DestroyInstance()
{
	if (instance)
	{
		delete instance;
	}
}

void StateMachine::Init(const char *path){
	ResourceManager::GetInstance();
	m_isExitCurrentState = false;
	m_isEnterNextState = false;
	m_currentState = new LogoState();
	m_currentState->OnInit();
	m_nextState = NULL;
}

void StateMachine::Update(float deltaTime)
{
	m_currentState->OnUpdate(deltaTime); // call update logics of current state
	if (m_isExitCurrentState)  //check and release current state
	{
		m_isExitCurrentState = false;
		m_currentState->OnExit();
		m_isEnterNextState = true;
	}
	if (m_isEnterNextState)  //check and intialize state
	{
		m_isEnterNextState = false;
		m_currentState = m_nextState;
		m_currentState->OnInit(); 
	}
}

void StateMachine::Render(Graphics* graphics)
{
	m_currentState->OnRender(graphics);
}

void StateMachine::SwitchState(State *state)
{
	m_nextState = state;
	m_isExitCurrentState = true;
}

State* StateMachine::GetState(){
	return m_currentState;
}


void StateMachine::TakeMousePosition(float x, float y, int mouseState)
{
	m_currentState->TakeMousePoint(x, y, mouseState);
}
