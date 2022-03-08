#include "LevelSpawner.h"
#include <iostream>



LevelSpawner::~LevelSpawner()
{
}

void LevelSpawner::Construct()
{
	Super::Construct();
}

void LevelSpawner::Start()
{
	Super::Start();
}

void LevelSpawner::Update()
{
	Super::Update();

	spawnerTimer -= 0.1;


	if (firstWave)
	{
		++smallCounter;
		if (smallCounter >= 300 && bigCounter < 10)
		{
			SpawnDroneEnemies(Vector3 {1000, 200, 0});
			SpawnDroneEnemies(Vector3 {1000, 400, 0});

			smallCounter = 0;
			bigCounter++;
		}

		if (bigCounter >= 10)
		{
			smallCounter = 0;
			bigCounter = 0;

			firstWave = false;
			secondWave = true;
			spawnerTimer = 300;
		}

	}

	if (secondWave && spawnerTimer <= 0)
	{
		++smallCounter;
		if (smallCounter == 100)
		{
			SpawnRusherEnemies(Vector3{ -10, 300, 0 });
		}
		if (smallCounter == 800 )
		{
			SpawnRusherEnemies(Vector3{ -10, 200, 0 });
			SpawnRusherEnemies(Vector3{ -10, 400, 0 });
			SpawnPowerUp(Vector3{1000, 500,0}, PowerUp::Companion);

			smallCounter = 0;
			secondWave = false;
			thirdWave = true;
			spawnerTimer = 300;
		}
	}

	if (thirdWave && spawnerTimer <= 0)
	{
		++smallCounter;
		if (smallCounter == 100)
		{
			SpawnLonerEnemies(Vector3{900, 700, 0});
		}
		if (smallCounter == 5000)
		{
			SpawnLonerEnemies(Vector3{ 900, 700, 0 });
			SpawnPowerUp(Vector3{1000, 100,0}, PowerUp::Weapon);
			smallCounter = 0;
			thirdWave = false;
			fourthWave = true;
			spawnerTimer = 400;
		}

	}

	if (fourthWave && spawnerTimer <= 0)
	{
		++smallCounter;
		if (smallCounter == 100)
		{
			SpawnAsteroid(Vector3{1000, 300,0}, Ast::RockBig);
		}
		if (smallCounter == 2000)
		{
			SpawnAsteroid(Vector3{ 1000, 500,0 }, Ast::MetalBig);
			SpawnAsteroid(Vector3{ 1000, 100,0 }, Ast::MetalSmall);
		}
		if (smallCounter == 3000)
		{
			SpawnAsteroid(Vector3{ 1000, 250,0 }, Ast::RockMedium);
			SpawnPowerUp(Vector3{1000, 450,0}, PowerUp::Weapon);
		}
		if (smallCounter == 4000)
		{
			SpawnAsteroid(Vector3{ 1000, 400,0 }, Ast::MetalMedium);
			SpawnAsteroid(Vector3{ 1000, 200,0 }, Ast::RockBig);
		}
		if (smallCounter == 5000)
		{
			SpawnAsteroid(Vector3{ 1000, 500,0 }, Ast::RockMedium);
			SpawnAsteroid(Vector3{ 1000, 100,0 }, Ast::RockMedium);
			SpawnAsteroid(Vector3{ 1000, 300,0 }, Ast::RockBig);

			smallCounter = 0;
			fourthWave = false;
			fifthWave = true;
			spawnerTimer = 400;
		}
	}

	if (fifthWave && spawnerTimer <= 0)
	{
		++smallCounter;
		if (smallCounter == 100)
		{
			SpawnPowerUp(Vector3{ 1000, 450,0 }, PowerUp::Companion);
			SpawnPowerUp(Vector3{ 1000, 200,0 }, PowerUp::Shield);
		}
		if (smallCounter == 1000)
		{
			SpawnAsteroid(Vector3{ 1000, 300,0 }, Ast::MetalBig);
		}
		if (smallCounter == 1500)
		{
			SpawnAsteroid(Vector3{ 1000, 300,0 }, Ast::MetalBig);
		}
		if (smallCounter == 2000)
		{
			SpawnAsteroid(Vector3{ 1000, 300,0 }, Ast::MetalBig);
		}
		if (smallCounter == 2500)
		{
			SpawnAsteroid(Vector3{ 1000, 300,0 }, Ast::MetalBig);

			fifthWave = false;
			sixthWave = true;
			spawnerTimer = 100;
		}

	}

	if (sixthWave && spawnerTimer <= 0)
	{
		++smallCounter;
		if (smallCounter >= 300 && bigCounter < 10)
		{
			SpawnDroneEnemies(Vector3{ 1000, 500, 0 });
			SpawnDroneEnemies(Vector3{ 1000, 450, 0 });
			smallCounter = 0;
			bigCounter++;
		}
		if (smallCounter == 1000)
		{
			SpawnAsteroid(Vector3{ 1000, 300,0 }, Ast::MetalBig);
		}
		if (smallCounter == 1500)
		{
			SpawnAsteroid(Vector3{ 1000, 300,0 }, Ast::MetalBig);
			SpawnRusherEnemies(Vector3{ 1000, 200, 0 });
			SpawnRusherEnemies(Vector3{ 1500, 200, 0 });
			sixthWave = false;
			seventhWave = true;
			spawnerTimer = 900;
		}
	}
	
	if (seventhWave && spawnerTimer <= 0)
	{
		SpawnBoss();
		seventhWave = false;
	}
}


void LevelSpawner::SpawnLonerEnemies(Vector3 location)
{
	myLevel->SpawnObject(new LonerEnemy(location, myLevel, hud, spaceship));
}

void LevelSpawner::SpawnRusherEnemies(Vector3 location)
{
	myLevel->SpawnObject(new RusherEnemy(location, myLevel, hud));
}

void LevelSpawner::SpawnDroneEnemies(Vector3 location)
{
	myLevel->SpawnObject(new DroneEnemy(location, myLevel, hud));
}

void LevelSpawner::SpawnAsteroid(Vector3 location, Ast type)
{
	Vector3 direction = {-15,0,0};

	switch (type)
	{
	case LevelSpawner::MetalBig:
		myLevel->SpawnObject(new MetalAsteroidBig(location));
		break;
	case LevelSpawner::MetalMedium:
		myLevel->SpawnObject(new MetalAsteroidMedium(location));
		break;
	case LevelSpawner::MetalSmall:
		myLevel->SpawnObject(new MetalAsteroidSmall(location));
		break;
	case LevelSpawner::RockBig:
		myLevel->SpawnObject(new RockAsteroidBig(location, direction, myLevel, hud));
		break;
	case LevelSpawner::RockMedium:
		myLevel->SpawnObject(new RockAsteroidMedium(location, direction, myLevel, hud));
		break;
	case LevelSpawner::RockSmall:
		myLevel->SpawnObject(new RockAsteroidSmall(location, direction, myLevel, hud));
		break;
	default:
		break;
	}
}

void LevelSpawner::SpawnPowerUp(Vector3 location, PowerUp powerUp)
{
	switch (powerUp)
	{
	case LevelSpawner::Companion:
		myLevel->SpawnObject(new CompanionPowerUp(location));
		break;
	case LevelSpawner::Weapon:
		myLevel->SpawnObject(new WeaponPowerUp(location));
		break;
	case LevelSpawner::Shield:
		myLevel->SpawnObject(new ShieldPowerUp(location));
		break;
	default:
		break;
	}
}

void LevelSpawner::SpawnBoss()
{
	myLevel->SpawnObject(new BossEnemy(Vector3{ 790,300,0 }, myLevel, spaceship, hud, engine, youWonMenu));
}


