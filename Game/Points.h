#pragma once
#include "Object.h"

class Points: public Object
{
public:
	Points(Vector3 initialPosition, int pointsQuantaty);

private:

	int points = 100;
	Vector3 iniPos = {};

	float lifeTimer = 500;
	float velocity = 0.1;

	using Super = Object;
	void Construct() override;
	void Start() override;
	void Update() override;
};

