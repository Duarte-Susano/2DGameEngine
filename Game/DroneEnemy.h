#pragma once
#include <iostream>
#include <vector>
#include "Vector3.h"
#include"Object.h"
#include "Level.h"
#include "LifeInterface.h"
#include "HUDScore.h"

class DroneEnemy: public Object, public LifeInterface
{
	using Super = Object;

public:

	DroneEnemy(Vector3 initialPosition, Level* rhsMylevel, HUDScore* hudScore);
	~DroneEnemy();
	bool isDead = false;

protected:

	Animation idle = { 1, 16, 1, true };
	Level* myLevel = nullptr;
	HUDScore* hud = nullptr;
	Image* myImage = nullptr;
	Sound* mySound = nullptr;

	int damageTimer = 100;
	int score = 100;

	float velocity = 10;
	float negativeVelocity = -10;
	float positiveVelocity = 10;

	void Construct() override;
	void Start() override;
	void Update() override;
	void DecreaseLife(int quantaty) override;

private:

	float heigth;
	float y;
	float time;
	Vector3 realLocation{};
};

