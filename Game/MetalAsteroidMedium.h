#pragma once
#include <iostream>
#include"Object.h"


class MetalAsteroidMedium: public Object
{

	using Super = Object;

public:

	MetalAsteroidMedium(Vector3 initialPosition);
	~MetalAsteroidMedium();
	bool isDead = false;

protected:

	Animation idle = { 1, 24, 3, true };
	Vector3 negativeVelocity = { -15, 0, 0 };
	void Construct() override;
	void Start() override;
	void Update() override;

private:

	Vector3 realLocation{};
};


