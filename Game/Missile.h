#pragma once
#include "Object.h"
#include "Vector3.h"
#include "Level.h"

class Missile : public Object
{
	//Use Super for Parent class
	using Super = Object;

public:
	
	enum Tier
	{
		light,
		medium,
		heavy,
	};

	//Constructor_Sets the initial position
	Missile(Vector3 initialPosition, Tier rhsTier);


	~Missile();

protected:
	//initial position
	Vector3 myInitialPosition = {};
	//velocity of the missile
	float velocity = 30.0f;
	bool hasExploded = false;
	int damage = 1;
	Tier myTier;

	//Animations
	Animation lightAnim = { 1, 2, 3, true };
	Animation mediumAnim = { 3, 4, 3, true };
	Animation heavyAnim = { 5, 6, 3, true };
	Animation explosion = {"XenonImages/explode16.bmp",5,2, 1, 10, 3, false };

	//Object functions
	void Construct() override;
	void Start() override;
	void Update() override;
	void FixUpdate() override;
};

