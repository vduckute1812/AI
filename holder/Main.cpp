#include <GameEngine.h>
#include "ResourceManager.h"
#include "StateMachine.h"
#include <stdlib.h>
#include "Define.h"
//#include <vld.h>

/**
* The main Program
**/
int main()
{
	// Init Game 
	Device *device = Device::GetInstance();
	device->InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	Graphics *graphics = device->GetGraphics();
	InputManager *inputManager = InputManager::GetInstance();
	StateMachine *stateMachine = StateMachine::GetInstance();

	ResourceManager::GetInstance();
	stateMachine->Init();

	// Game Loop
	while (device->IsRunning())
	{
		// Update game status 
		// deltaTime = time of that frame
		float deltaTime = GameTime::GetFrameTime();

		TouchData *touchData = inputManager->GetTouch();
		if (touchData != NULL
			&& (touchData->state == TOUCH_DOWN || touchData->state == TOUCH_MOVE)
			)
		{
			// handle touch
			Logger::Debug("Touch::", "Touch state: %d x: %f y: %f", touchData->state, touchData->position.x, touchData->position.y);
		}
		//Update
		stateMachine->Update(deltaTime);

		// Render the scene
		graphics->ClearScreen();
		stateMachine->Render(graphics);
		//graphics->SetColor(1.0f, 0.0f, 0.0f);
		//graphics->DrawArc(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, RADIUS);
		//graphics->DrawRect(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, BAR_WIDTH, BAR_HEIGHT);
	}

	//Exit Game
    InputManager::DestroyInstance();
    Device::DestroyInstance();
    return 0;
}