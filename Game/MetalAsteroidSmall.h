#pragma once
#include <iostream>
#include"Object.h"


class MetalAsteroidSmall: public Object
{

	using Super = Object;

public:

	MetalAsteroidSmall(Vector3 initialPosition);
	~MetalAsteroidSmall();
	bool isDead = false;

protected:

	Animation idle = { 1, 16, 3, true };
	Vector3 negativeVelocity = { -15, 0, 0 };
	void Construct() override;
	void Start() override;
	void Update() override;

private:

	Vector3 realLocation{};
};

