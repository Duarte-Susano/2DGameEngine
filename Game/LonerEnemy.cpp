#include "LonerEnemy.h"
#include "Points.h"

LonerEnemy::~LonerEnemy()
{
	myLevel = nullptr;
}

LonerEnemy::LonerEnemy(Vector3 location, Level* rhsMyLevel, HUDScore* hudScore, Object* rhsSpaceship)
{
	realLocation = location;
	myLevel = rhsMyLevel;
	hud = hudScore;
	spaceShip = rhsSpaceship;
}

void LonerEnemy::Construct()
{
	Super::Construct();

	myImage = AddComponent<Image>("XenonImages/LonerB.bmp", 4,4,2);
	AddComponent<Collider>();
	mySound = AddComponent<Sound>();
	
}

void LonerEnemy::Start()
{
	Super::Start();
	GetComponent<Transform>().position = realLocation;

	GetComponent<Image>().PlayAnimation(idle);


	//Create Collider
	GetComponent<Collider>().MakeCollider(
		GetComponent<Transform>().position,
		GetComponent<Collider>().DynamicBody,
		GetComponent<Image>().imageWidth / 4,
		GetComponent<Image>().imageHeight / 4,
		0.0f,
		0.0f,
		0.0f,
		true,
		true);

	GetComponent<Collider>().SetVelocity(negativeVelocity);

	life = 8;
}

void LonerEnemy::Update()
{
	Super::Update();

	if (isDead)
	{
		Destroy(this);
	}
	

	if (myImage->color.x > 10)
	{
		--damageTimer;
	}

	if (damageTimer <= 0)
	{
		myImage->color = { 1,1,1 };
		damageTimer = 100;
	}

	GetComponent<Transform>().position = GetComponent<Collider>().GetPosition();

	//Adding the movement to the transform

	if (GetComponent<Transform>().position.y >= 450)
	{
		GetComponent<Collider>().SetVelocity(negativeVelocity);
	}
	if (GetComponent<Transform>().position.y <= 150)
	{
		GetComponent<Collider>().SetVelocity(positiveVelocity);
	}


	if (GetComponent<Collider>().asCollided
		&& GetComponent<Collider>().GetCollisionResultObject() != nullptr
		&& (GetComponent<Collider>().GetCollisionResultObject()->GetTag() == "Spaceship"
		|| GetComponent<Collider>().GetCollisionResultObject()->GetTag() == "Companion"))
	{
		LifeInterface* Ilife = dynamic_cast<LifeInterface*>(GetComponent<Collider>().GetCollisionResultObject());
		Ilife->DecreaseLife(1);
		isDead = true;
		GetComponent<Collider>().asCollided = false;
	}
	

	//timer to shoot
	shootTime += 0.1f;
	//std::cout << timePipe->GetDeltaTIme() << std::endl;
	if (shootTime > timeToShoot)
	{
		SpwanEnemyAttack();
		shootTime = 0;
	}
}

void LonerEnemy::SpwanEnemyAttack()
{
	Vector3 missilePosition = GetComponent<Transform>().position;

	spaceshipVec = spaceShip->GetComponent<Transform>().position;

	float xDirection = spaceshipVec.x - missilePosition.x;
	float yDirection = spaceshipVec.y - missilePosition.y;

	projDirection.x = xDirection;
	projDirection.y = -yDirection;

	projDirection.Normalize();

	myLevel->SpawnObject(new EnemyAttack(missilePosition, projDirection, myLevel));
}

void LonerEnemy::DecreaseLife(int quantaty)
{
	LifeInterface::DecreaseLife(quantaty);

	myImage->color = { 100, 100, 100 };

	if (!isAlive)
	{
		mySound->PlaySound("SoundFiles/Explosion1.wav");
		myLevel->SpawnObject(new Points(GetComponent<Transform>().position, score));
		hud->AddScore(score);
		isDead = true;
	}
}