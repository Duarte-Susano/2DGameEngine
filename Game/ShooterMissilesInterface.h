#pragma once
#include "Missile.h"
#include "Vector3.h"
#include "Level.h"

class ShooterMissilesInterface
{
public:
	void SpawnMissile(Vector3 position, Level* level);
	void MissilePowerUp();
	Missile::Tier missileTier;
	virtual ~ShooterMissilesInterface();
};

