#pragma once
#include "Object.h"
#include "Level.h"
#include "HUDScore.h"

#include "LonerEnemy.h"
#include "RusherEnemy.h"
#include "DroneEnemy.h"
#include "BossEnemy.h"

#include "MetalAsteroidBig.h"
#include "MetalAsteroidMedium.h"
#include "MetalAsteroidSmall.h"
#include "RockAsteroidBig.h"
#include "RockAsteroidMedium.h"
#include "RockAsteroidSmall.h"

#include "CompanionPowerUp.h"
#include "ShieldPowerUp.h"
#include "WeaponPowerUp.h"

#include "GameEngine.h"

class LevelSpawner: public Object
{
	using Super = Object;

public: 

	LevelSpawner(Level* level, HUDScore* hudScore, Object* rhsSpaceship, GameEngine* gameEngine, Level* youWonLevel) :
	myLevel{ level }, hud{hudScore}, spaceship{rhsSpaceship}, engine{gameEngine}, youWonMenu{youWonLevel} {};
	~LevelSpawner();

	enum Ast
	{
		MetalBig,
		MetalMedium,
		MetalSmall,
		RockBig,
		RockMedium,
		RockSmall,
	};

	enum PowerUp
	{
		Companion,
		Weapon,
		Shield,
	};

	//Spawns Loner Enenmie
	void SpawnLonerEnemies(Vector3 location);

	//Spawns Rusher Enemie
	void SpawnRusherEnemies(Vector3 location);

	//Spawn Drone Enemies
	void SpawnDroneEnemies(Vector3 location);

	//Spawn Asteroid
	void SpawnAsteroid(Vector3 location, Ast type);

	void SpawnPowerUp(Vector3 location, PowerUp powerUp);

	void SpawnBoss();

private:
	Object* spaceship = nullptr;
	HUDScore* hud = nullptr;
	LonerEnemy* myLonerEnemy = nullptr;
	RusherEnemy* myRusherEnemy2 = nullptr;
	RusherEnemy* myRusherEnemy = nullptr;
	DroneEnemy* myDroneEnemy = nullptr;
	DroneEnemy* myDroneEnemy2 = nullptr;
	Level* myLevel = nullptr;
	GameEngine* engine = nullptr;
	Level* youWonMenu = nullptr;

	float spawnerTimer = 0;
	int smallCounter;
	int bigCounter;

	bool firstWave = true;
	bool secondWave = false;
	bool thirdWave = false;
	bool fourthWave = false;
	bool fifthWave = false;
	bool sixthWave = false;
	bool seventhWave = false;

	void Construct() override;
	void Start() override;
	void Update() override;
};

