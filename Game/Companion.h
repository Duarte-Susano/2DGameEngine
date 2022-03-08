#pragma once
#include "Object.h"
#include "LifeInterface.h"
#include "ShooterMissilesInterface.h"
#include "Spaceship.h"
#include "Level.h"

class Companion: public Object, public LifeInterface, public ShooterMissilesInterface
{
	using Super = Object;

public:
	Companion(Spaceship* mySpaceship, bool isLeftCompanion, Level* level): mySpaceship{mySpaceship},
	leftCompanion{isLeftCompanion},
	myLevel{level}{};
	~Companion(){};

protected:

	bool firstShoot = false;
	bool shooting = false;
	float timeToShoot = 30.0f;
	float shootTime = 0.0f;
	float yOffSet = 50.0f;
	float velocity = 0.05;
	float xOffSet = 0.0f;
	int damageTimer = 100;
	
	bool leftCompanion = true;
	bool die = false;

	Animation Idle = { 1, 16, 3, true };
	Animation Dead = { 16, 20, 3, false };

	Spaceship* mySpaceship = nullptr;
	Level* myLevel = nullptr;
	Image* myImage = nullptr;
	Sound* mySound = nullptr;

	void Construct() override;
	void Start() override;
	void Update() override;
	void DecreaseLife(int quantaty) override;
};

