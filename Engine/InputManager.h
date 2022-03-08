#pragma once
#include "SDL.h"
#include "SDL_gamecontroller.h"
#include "Inputs.h"

class InputManager
{
public:
	//Returns instance
	static InputManager* GetInputManager();

	//Start handle sistem to the keyboard
	void HandleInputsKeyboard();
	//Start handle sistem to the gamepad
	void HandleInputsGamepad();
	//checks the inputs
	void InputsGamePadLoop(SDL_Event gamepadEvent);
	//returns inputs
	Inputs GetInputs();

private:
	//my instance
	static InputManager* instance;
 
	//Struct of the inputs
	Inputs inputs;
	//controller of state of keys
	const Uint8* myKeyState;
	//reference to use game controllers
	SDL_GameController* myGameController;
	//to use the controller axies
	SDL_GameControllerAxis gameContollerAxis;
};

