#pragma once
#include <iostream>
#include "EnemyAttack.h"
#include "Level.h"
#include "Vector3.h"
#include "LifeInterface.h"
#include "HUDScore.h"

class LonerEnemy: public Object, public LifeInterface
{
	using Super = Object;

	Animation idle = {1,16,1,true};

public:

	~LonerEnemy();

	LonerEnemy(Vector3 location, Level* rhsMyLevel, HUDScore* hudScore, Object* rhsSpaceship);

	bool isDead = false;

protected:

	Level* myLevel = nullptr;
	HUDScore* hud = nullptr;
	Object* spaceShip;
	Image* myImage = nullptr;
	Sound* mySound = nullptr;

	int damageTimer = 100;
	int score = 500;
	float timeToShoot = 50.0f;

	void Construct() override;
	void Start() override;
	void Update() override;
	void DecreaseLife(int quantaty) override;

private:

	Vector3 realLocation{};
	Vector3 positiveVelocity = { -5, 7 ,0 };
	Vector3 negativeVelocity = { -5,-7,0 };
	Vector3 spaceshipVec;
	Vector3 projDirection;
	Vector3 enemyAttckVec;

	float y;
	float x;
	float time = 0;
	float shootTime = 0.0f;

	void SpwanEnemyAttack();
};

