#include "InputManager.h"

#include <iostream>


void::InputManager::HandleInputsGamepad()
{

	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			char* mapping;
			std::cout << "Index '" << i << "' is a compatible controller, named '" << SDL_GameControllerNameForIndex(i) << "'" << std::endl;
			myGameController = SDL_GameControllerOpen(i);
			mapping = SDL_GameControllerMapping(myGameController);
			std::cout << "Controller " << i << " is mapped as \"" << mapping << std::endl;
			SDL_free(mapping);
		}

		else {
			std::cout << "Index '" << i << "' is not a compatible controller." << std::endl;
		}
	}
}

InputManager* InputManager::GetInputManager()
{
	if(instance == nullptr)
		instance = new InputManager;
	return instance;
}

void::InputManager::HandleInputsKeyboard()
{
	inputs.ResetKeyboardInputs();
	myKeyState = SDL_GetKeyboardState(NULL);

	//Keyboard Arrows:
	if (myKeyState[SDL_SCANCODE_UP])
	{	
		inputs.UP = true;
	}
	if (myKeyState[SDL_SCANCODE_DOWN])
	{
		inputs.DOWN = true;
	}
	if (myKeyState[SDL_SCANCODE_RIGHT])
	{
		inputs.RIGHT = true;
	}
	if (myKeyState[SDL_SCANCODE_LEFT])
	{
		inputs.LEFT = true;
	}

	//WASD
	if (myKeyState[SDL_SCANCODE_W])
	{
		inputs.W = true;
	}
	if (myKeyState[SDL_SCANCODE_A])
	{
		inputs.A = true;
	}
	if (myKeyState[SDL_SCANCODE_S])
	{
		inputs.S = true;
	}
	if (myKeyState[SDL_SCANCODE_D])
	{
		inputs.D = true;
	}

	//Space
	if (myKeyState[SDL_SCANCODE_SPACE])
	{
		inputs.SPACE = true;
	}

	//ZXC
	if (myKeyState[SDL_SCANCODE_Z])
	{
		inputs.Z = true;
	}
	if (myKeyState[SDL_SCANCODE_X])
	{
		inputs.X = true;
	}
	if (myKeyState[SDL_SCANCODE_C])
	{
		inputs.C = true;
	}


	//Special keys
	if (myKeyState[SDL_SCANCODE_ESCAPE])
	{
		inputs.ESC = true;
	}
	if (myKeyState[SDL_SCANCODE_EXECUTE])
	{
		inputs.ENTER = true;
	}
}


void InputManager::InputsGamePadLoop(SDL_Event gamepadEvent)
{

	//Button Down
	if (gamepadEvent.type == SDL_CONTROLLERBUTTONDOWN)
	{
		//ABXY
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_A)
		{
			inputs.CTRL_A = true;
		}
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_B)
		{
			inputs.CTRL_B = true;
		}
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_X)
		{
			inputs.CTRL_X = true;
		}
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
		{
			inputs.CTRL_Y = true;
		}

		//DPAD
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP)
		{
			inputs.CTRL_DPAD_UP = true;
		}
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
		{
			inputs.CTRL_DPAD_DOWN = true;
		}
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
		{
			inputs.CTRL_DPAD_LEFT = true;
		}
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
		{
			inputs.CTRL_DPAD_RIGHT = true;
		}

		//Special keys
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_BACK)
		{
			inputs.CTRL_BACK = true;
		}
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_START)
		{
			inputs.CTRL_START = true;
		}
	}


	//Button UP
	if (gamepadEvent.type == SDL_CONTROLLERBUTTONUP)
	{
		//ABXY
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_A)
		{
			inputs.CTRL_A = false;
		}
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_B)
		{
			inputs.CTRL_B = false;
		}
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_X)
		{
			inputs.CTRL_X = false;
		}
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
		{
			inputs.CTRL_Y = false;
		}

		//DPAD
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP)
		{
			inputs.CTRL_DPAD_UP = false;
		}
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
		{
			inputs.CTRL_DPAD_DOWN = false;
		}
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
		{
			inputs.CTRL_DPAD_LEFT = false;
		}
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
		{
			inputs.CTRL_DPAD_RIGHT = false;
		}

		//Special keys
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_BACK)
		{
			inputs.CTRL_BACK = false;
		}
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_START)
		{
			inputs.CTRL_START = false;
		}
	}


	if (gamepadEvent.type == SDL_CONTROLLERAXISMOTION)
	{
		if (gamepadEvent.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
		{
			float f = gamepadEvent.caxis.value;
			if (f < 0)
			{
				f /= 32768;
			}
			else
			{
				f /= 32767;
			}
			inputs.CTRL_ANALOG_LEFT_X = f;
		}
		if (gamepadEvent.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
		{
			float f = gamepadEvent.caxis.value;
			if (f < 0)
			{
				f /= 32768;
			}
			else
			{
				f /= 32767;
			}
			inputs.CTRL_ANALOG_LEFT_Y = f;
		}
		if (gamepadEvent.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX)
		{
			float f = gamepadEvent.caxis.value;
			if (f < 0)
			{
				f /= 32768;
			}
			else
			{
				f /= 32767;
			}
			inputs.CTRL_ANALOG_RIGHT_X = f;
		}
		if (gamepadEvent.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY)
		{
			float f = gamepadEvent.caxis.value;
			if (f < 0)
			{
				f /= 32768;
			}
			else
			{
				f /= 32767;
			}
			inputs.CTRL_ANALOG_RIGHT_Y = f;
		}
	}
}

Inputs InputManager::GetInputs()
{
	return inputs;
}
