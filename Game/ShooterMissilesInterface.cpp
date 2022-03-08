#include "ShooterMissilesInterface.h"

void ShooterMissilesInterface::SpawnMissile(Vector3 position, Level* level)
{
	level->SpawnObject(new Missile(position, missileTier));
}

void ShooterMissilesInterface::MissilePowerUp()
{
	switch (missileTier)
	{
	case Missile::light:
		missileTier = Missile::Tier::medium;
		break;
	case Missile::medium:
		missileTier = Missile::Tier::heavy;
		break;
	case Missile::heavy:
		break;
	default:
		break;
	}
}

ShooterMissilesInterface::~ShooterMissilesInterface()
{
}
