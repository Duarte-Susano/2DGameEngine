#pragma once
#include "Object.h"
#include "Inputs.h"
#include "Controller.h"

class ControllableCharacter: public Object
{
public:
	//Construct function
	void Construct() override;

	//start function
	void Start() override;

	//update function
	void Update() override;

	//Struct with all inputs
	Inputs inputs;
};

