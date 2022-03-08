#pragma once
#include"Object.h"
#include "Level.h"
#include "LifeInterface.h"
#include "HUDScore.h"

class RockAsteroidMedium : public Object, public LifeInterface
{

	using Super = Object;

public:

	RockAsteroidMedium(Vector3 initialPosition, Vector3 Direction,  Level* rhsMylevel, HUDScore* hudScore);
	~RockAsteroidMedium();
	bool isDead = false;

protected:
	Image* myImage = nullptr;
	HUDScore* hud = nullptr;
	Animation idle = { 1, 24, 3, true };
	Level* myLevel = nullptr;
	Vector3 realLocation{};
	Vector3 AsteroidDirection{};
	Sound* mySound = nullptr;

	int damageTimer = 100;
	int score = 200;

	void Construct() override;
	void Start() override;
	void Update() override;
	void DecreaseLife(int quantaty) override;


};
