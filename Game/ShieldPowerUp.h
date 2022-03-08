#pragma once
#include "Object.h"

class ShieldPowerUp : public Object
{
public:
	ShieldPowerUp(Vector3 iniPos):initialPosition{iniPos}{}

protected:
	using Super = Object;

	Image* image = nullptr;
	Animation animation = { 1, 8, 3,true };
	Vector3 initialPosition = {};
	Sound* mySound = nullptr;

	void Construct() override;
	void Start() override;
	void Update() override;
};

