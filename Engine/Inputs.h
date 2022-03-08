#pragma once
struct Inputs
{
	//Keyboard buttons
	bool UP;
	bool DOWN;
	bool LEFT;
	bool RIGHT;

	bool W;
	bool A;
	bool S;
	bool D;

	bool Z;
	bool X;
	bool C;

	bool SPACE;
	bool ESC;
	bool ENTER;


	//Controller buttons
	bool CTRL_A;
	bool CTRL_B;
	bool CTRL_X;
	bool CTRL_Y;

	bool CTRL_DPAD_UP;
	bool CTRL_DPAD_DOWN;
	bool CTRL_DPAD_LEFT;
	bool CTRL_DPAD_RIGHT;

	bool CTRL_START;
	bool CTRL_BACK;

	//Controller axis
	float CTRL_ANALOG_LEFT_X = 0;
	float CTRL_ANALOG_LEFT_Y = 0;
	float CTRL_ANALOG_RIGHT_X = 0;
	float CTRL_ANALOG_RIGHT_Y = 0;

	//Resets all bools of the keyboard to false
	void ResetKeyboardInputs();
};

