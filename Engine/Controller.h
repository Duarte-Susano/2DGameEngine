#pragma once
#include "Component.h"
#include "Inputs.h"

class Controller: public Component
{
public:
	//Destructor
	~Controller();
	//Get true if key is down
	bool IsKeyDown(int input);
	//Structore with all inputs
	Inputs inputs;
private:
	void Start() override;
	void Update() override;

	//Reference to input manager
	class InputManager* inputManager {};
};

