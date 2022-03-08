#include "BossEnemy.h"
#include "BossEyes.h"

BossEnemy::BossEnemy(Vector3 initialPosition, Level* rhsMylevel, Object* rhsSpaceship, HUDScore* hudScore, GameEngine* myEngine, Level* EndMenu)
{
	realLocation = initialPosition;
	myLevel = rhsMylevel;
	spaceShip = rhsSpaceship;
	hud = hudScore;
	engine = myEngine;
	finalMenu = EndMenu;
}

BossEnemy::~BossEnemy()
{
	myLevel = nullptr;
	spaceShip = nullptr;
}

void BossEnemy::Construct()
{
	Super::Construct();

	myImageBoss = AddComponent<Image>("XenonImages/Boss.bmp", 1, 1, -1);
}

void BossEnemy::Start()
{
	GetComponent<Transform>().rotation = Vector3{0 ,0,-90};
	GetComponent<Transform>().scale = Vector3{ 1.5f, 1.5f , 1.f};
	GetComponent<Transform>().position = realLocation;

	SpawnBossEyes();

}

void BossEnemy::Update()
{
	//timer to shoot
	shootTime += 0.1f;

	if (shootTime > timeToShoot)
	{
		SpwanBossAttack();
		shootTime = 0;
	}
}


void BossEnemy::SpwanBossAttack()
{
	Vector3 missilePosition = Vector3{ 630,300,0 };

	spaceshipVec = spaceShip->GetComponent<Transform>().position;

	float xDirection = spaceshipVec.x - missilePosition.x;
	float yDirection = spaceshipVec.y - missilePosition.y;

	projDirection.x = xDirection;
	projDirection.y = -yDirection;

	projDirection.Normalize();

	myLevel->SpawnObject(new EnemyAttack(missilePosition, projDirection, myLevel));
}

void BossEnemy::SpawnBossEyes()
{
	
	myLevel->SpawnObject(new BossEyes(Vector3{ 730,515,0 }, myLevel, BossEyes::BossEye::LeftEye1, hud, this));
	myLevel->SpawnObject(new BossEyes(Vector3{ 775,460,0 }, myLevel, BossEyes::BossEye::LeftEye2, hud, this));
	myLevel->SpawnObject(new BossEyes(Vector3{ 740,380,0 }, myLevel, BossEyes::BossEye::LeftEye3, hud, this));
	myLevel->SpawnObject(new BossEyes(Vector3{ 743,225,0 }, myLevel, BossEyes::BossEye::RightEye1, hud, this));
	myLevel->SpawnObject(new BossEyes(Vector3{ 775,145,0 }, myLevel, BossEyes::BossEye::RightEye2, hud, this));
	myLevel->SpawnObject(new BossEyes(Vector3{ 730,95,0 }, myLevel, BossEyes::BossEye::RightEye3, hud, this));
}

void BossEnemy::EyeDied()
{
	--remainingEyes;
	if (remainingEyes <= 0)
	{
		engine->LoadLevel(finalMenu);
		Destroy(this);
	}
}
