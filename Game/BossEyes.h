#pragma once
#include <iostream>
#include <vector>
#include "Vector3.h"
#include "Object.h"
#include "LifeInterface.h"
#include "HUDScore.h"
#include "EnemyAttack.h"
#include "BossEnemy.h"


class BossEyes : public Object, public LifeInterface
{
	using Super = Object;



public:

	enum  BossEye
	{
		LeftEye1,
		LeftEye2,
		LeftEye3,
		RightEye1,
		RightEye2,
		RightEye3,
	};

	bool isDead;
	BossEyes(Vector3 initialPosition, Level* rhsMylevel, BossEyes::BossEye type, HUDScore* myHUD, BossEnemy* myBoss);
	~BossEyes();


protected:

	Animation EyeLeft1Anim = { 7, 7, 1, true };
	Animation EyeLeft2Anim = { 8, 8, 1, true };
	Animation EyeLeft3Anim = { 9, 9, 1, true };
	Animation EyeRight1Anim = { 10, 10, 1, true };
	Animation EyeRight2Anim = { 11, 11, 1, true };
	Animation EyeRight3Anim = { 12, 12, 1, true };

	Level* myLevel = nullptr;
	HUDScore* hud = nullptr;
	Image* myImageEye = nullptr;
	Animation EyeAnimation;
	BossEnemy* boss = nullptr;

	int damageTimer = 100;
	int score = 555;

	void Construct() override;
	void Start() override;
	void Update() override;
	void DecreaseLife(int quantaty) override;


private:

	Vector3 realLocation{};

	Vector3 spaceshipVec;
	Vector3 projDirection;
	Vector3 enemyAttckVec;

};

