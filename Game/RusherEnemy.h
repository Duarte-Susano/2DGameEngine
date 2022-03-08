#pragma once
#include <iostream>
#include <vector>
#include "Vector3.h"
#include"Object.h"
#include "Level.h"
#include "LifeInterface.h"
#include "HUDScore.h"

class RusherEnemy: public Object, public LifeInterface
{
	using Super = Object;

public:

	RusherEnemy(Vector3 initialPosition, Level* rhsMylevel, HUDScore* hudScore);
	~RusherEnemy();

	bool isDead = false;

protected:
	int damageTimer = 100;
	Image* myImage = nullptr;
	Animation idle = { 1, 24, 1, true };
	Vector3 positiveVelocity = { 25, 0, 0 };
	Vector3 negativeVelocity = { -25, 0, 0 };
	Vector3 realLocation{};
	Level* myLevel = nullptr;
	HUDScore* hud = nullptr;
	Sound* mySound = nullptr;

	int score = 300;


	void Construct() override;
	void Start() override;
	void Update() override;
	void DecreaseLife(int quantaty) override;
};

