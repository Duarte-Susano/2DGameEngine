#pragma once
#include <iostream>
#include"Object.h"

class MetalAsteroidBig: public Object
{

	using Super = Object;

public:

	MetalAsteroidBig(Vector3 initialPosition);
	~MetalAsteroidBig();
	bool isDead = false;

protected:

	Animation idle = { 1, 25, 3, true };
	Vector3 negativeVelocity = { -15, 0, 0 };
	void Construct() override;
	void Start() override;
	void Update() override;

private:

	Vector3 realLocation{};
};



