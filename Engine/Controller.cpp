#include "Controller.h"
#include <iostream>
#include "InputManager.h"

Controller::~Controller()
{
inputManager = nullptr;
}

bool Controller::IsKeyDown(int input)
{
	if(input > 0)
		return true;
	return false;
}

void Controller::Start()
{
	inputManager = inputManager->GetInputManager();
}

void Controller::Update()
{
	inputs = inputManager->GetInputs();
}
