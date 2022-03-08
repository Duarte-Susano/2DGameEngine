#pragma once
#include <iostream>
#include <vector>
#include "Vector3.h"
#include "Object.h"
#include "Level.h"
#include "EnemyAttack.h";
#include "HUDScore.h"

#include "GameEngine.h"
#include "Level.h"


class BossEnemy: public Object
{

	using Super = Object;

public:

	BossEnemy(Vector3 initialPosition, Level* rhsMylevel, Object* rhsSpaceship, HUDScore* hudScore, GameEngine* myEngine, Level* EndMenu);
	~BossEnemy();

	void SpwanBossAttack();
	void SpawnBossEyes();

	void EyeDied();

protected:

	Level* myLevel = nullptr;
	GameEngine* engine = nullptr;
	Level* finalMenu = nullptr;
	Image* myImageBoss = nullptr;
	Object* spaceShip;
	class BossEyes* myBossEyes;
	HUDScore* hud = nullptr;

	void Construct() override;
	void Start() override;
	void Update() override;

private:

	float timeToShoot = 20.0f;
	float shootTime;
	Vector3 realLocation{};
	Vector3 projDirection;
	Vector3 enemyAttckVec;
	Vector3 spaceshipVec;
	int remainingEyes = 6;

};

