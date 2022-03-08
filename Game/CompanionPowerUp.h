#pragma once
#include "Object.h"

class CompanionPowerUp: public Object
{
public:
	CompanionPowerUp(Vector3 iniPos): initialPosition {iniPos} {};

protected:
	using Super = Object;

	Image* image = nullptr;
	Animation animation = {1, 16, 3, true};
	Sound* mySound = nullptr;

	Vector3 initialPosition = {};

	void Construct() override;
	void Start() override;
	void Update() override;
};

