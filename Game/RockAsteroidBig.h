#pragma once
#include "Object.h"
#include "Level.h"
#include "LifeInterface.h"
#include "HUDScore.h"

class RockAsteroidBig : public Object, public LifeInterface
{

	using Super = Object;

public:

	RockAsteroidBig(Vector3 initialPosition, Vector3 Direction ,Level* rhsMylevel, HUDScore* hudScore);
	~RockAsteroidBig();
	bool isDead = false;

protected:
	Image* myImage = nullptr;
	HUDScore* hud = nullptr;
	Animation idle = { 1, 25, 3, true };
	Level* myLevel = nullptr;
	Vector3 realLocation{};
	Vector3 AsteroidDirection{};
	Sound* mySound = nullptr;

	int damageTimer = 100;
	int score = 300;

	void Construct() override;
	void Start() override;
	void Update() override;
	void DecreaseLife(int quantaty) override;

};

