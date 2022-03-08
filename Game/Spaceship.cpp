#include "Spaceship.h"
#include "Companion.h"

Spaceship::~Spaceship()
{
	myLevel = nullptr;
}

void Spaceship::SpawnCompanion()
{
	if (!companionLeft)
	{
		myLevel->SpawnObject(new Companion(this, true, myLevel));
		companionLeft = true;
	}
	else if(!companionRight)
	{
		myLevel->SpawnObject(new Companion(this, false, myLevel));
		companionRight = true;
	}
}

void Spaceship::AddLife(int quantaty)
{
	life += quantaty;
	if (life > maxLife)
	{
		life = maxLife;
	}

	myHUD->UpdateLife(life);
}

void Spaceship::AddGameLifes(int quantaty)
{
	gameLifes += quantaty;
	if (gameLifes > 3)
	{
		gameLifes = 3;
	}

	myHUD->UpdateSpaceships(gameLifes);
}

void Spaceship::Construct()
{
	Super::Construct();
	spaceship = AddComponent<Image>("XenonImages/Ship2.bmp", 7, 3, 6);

	mySound = AddComponent<Sound>();

	maxLife = 10;
	life = 10;

	//burners
	mainBurner = AddComponent<Image>("XenonImages/Burner1.bmp",1,1,5);
	mainBurner->xOffSet = -45;

	leftBottomBurner = AddComponent<Image>("XenonImages/Burner6.bmp", 2, 1, 5);
	leftBottomBurner->xOffSet = -27;
	leftBottomBurner->yOffSet = 27;
	leftBottomBurner->isVisible = false;

	rightBottomBurner = AddComponent<Image>("XenonImages/Burner5.bmp", 2, 1, 5);
	rightBottomBurner->xOffSet = -27;
	rightBottomBurner->yOffSet = -27;
	rightBottomBurner->isVisible = false;

	leftTopBurner = AddComponent<Image>("XenonImages/Burner3.bmp", 2, 1, 5);
	leftTopBurner->xOffSet = 25;
	leftTopBurner->yOffSet = 25;
	leftTopBurner->isVisible = false;

	rightTopBurner = AddComponent<Image>("XenonImages/Burner4.bmp", 2, 1, 5);
	rightTopBurner->xOffSet = 25;
	rightTopBurner->yOffSet = -25;
	rightTopBurner->isVisible = false;


	AddComponent<Collider>();
}

void Spaceship::Start()
{
	Super::Start();
	SetTag("Spaceship");

	timePipe = timePipe->GetTimePipelineInstance();

	unbTimer = maxUnbTimer;

	GetComponent<Transform>().position.x = 0;
	GetComponent<Transform>().position.y = 300;
	GetComponent<Transform>().rotation = {0,0,-90};

	if (unbAnimation)
	{
		spaceship->PlayAnimation(unbIdle);
	}
	else
	{
		spaceship->PlayAnimation(idle);
	}


	//Create Collider
	GetComponent<Collider>().MakeCollider(
		GetComponent<Transform>().position,
		GetComponent<Collider>().DynamicBody,
		(spaceship->imageWidth / spaceship->nColumns),
		(spaceship->imageHeight / spaceship->nRows),
		0.0f,
		0.0f,
		0.0f,
		true,
		true);

	myHUD->UpdateLife(life);
	myHUD->UpdateSpaceships(gameLifes);
}


void Spaceship::Update()
{
	Super::Update();

	//reset movement
	movement.x = 0;
	movement.y = 0;

	//keyboard inputs __ Adds the velocity to the movement according to the input
	if (inputs.A || inputs.LEFT)
	{
		movement.x -= velocity;
	}
	if (inputs.D || inputs.RIGHT)
	{
		movement.x += velocity;
	}
	if (inputs.W || inputs.UP)
	{
		movement.y += velocity;
	}
	if (inputs.S || inputs.DOWN)
	{
		movement.y -= velocity;
	}

	shooting = false;

	//SHOOT
	if (inputs.SPACE || inputs.CTRL_A)
	{
		if (!firstShoot)
		{
			firstShoot = true;
			mySound->PlaySound("SoundFiles/Gun2.wav");
			SpawnMissile(GetComponent<Transform>().position, myLevel);
			shootTime = 0;
		}
		shooting = true;
	}
	else
	{
		firstShoot = false;
		shooting = false;
	}

	//timer to shoot
	shootTime += 0.1f;
	//std::cout << timePipe->GetDeltaTIme() << std::endl;
	if (shootTime > timeToShoot)
	{
		if (shooting)
		{
			mySound->PlaySound("SoundFiles/Gun2.wav");
			SpawnMissile(GetComponent<Transform>().position, myLevel);
		}
		shootTime = 0;
	}

	//Controller inputs _ Adds the velocity * axis value to the movement

	if (inputs.CTRL_ANALOG_LEFT_X > 0.1 || inputs.CTRL_ANALOG_LEFT_X < -0.1)
	{
		movement.x += inputs.CTRL_ANALOG_LEFT_X;
	}

	if (inputs.CTRL_ANALOG_LEFT_Y > 0.1 || inputs.CTRL_ANALOG_LEFT_Y < -0.1)
	{
		movement.y -= inputs.CTRL_ANALOG_LEFT_Y;
	}

	//Animations



	if (movement.y > 0 && spaceship->GetCurrentAnimation() != turningLeft)
	{
		spaceship->PlayAnimation(turningLeft);
	}
	else if (movement.y < 0 && spaceship->GetCurrentAnimation() != turningRight)
	{
		spaceship->PlayAnimation(turningRight);
	}
	else if (movement.y == 0 && spaceship->GetCurrentAnimation() == turningLeft)
	{
		spaceship->PlayAnimation(leftToCenter);
	}
	else if (movement.y == 0 && spaceship->GetCurrentAnimation() == turningRight)
	{
		spaceship->PlayAnimation(rightToCenter);
	}
	else if (movement.y == 0 && spaceship->EndOfAnimation())
	{
		spaceship->PlayAnimation(idle);
	}
	
	if (unbAnimation)
	{
		spaceship->framePositionRow = 1;
	}
	else
	{
		spaceship->framePositionRow = 0;
	}

	leftBottomBurner->isVisible = false;
	rightBottomBurner->isVisible = false;
	leftTopBurner->isVisible = false;
	rightTopBurner->isVisible = false;

	if (movement.x > 0 && movement.y < 0)
	{
		leftBottomBurner->isVisible = true;
	}
	else if (movement.x > 0 && movement.y > 0)
	{
		rightBottomBurner->isVisible = true;
	}
	else if (movement.x < 0 && movement.y < 0)
	{
		leftTopBurner->isVisible = true;
	}
	else if (movement.x < 0 && movement.y > 0)
	{
		rightTopBurner->isVisible = true;
	}
	else if (movement.y < 0 && movement.x == 0)
	{
		leftBottomBurner->isVisible = true;
		leftTopBurner->isVisible = true;
	}
	else if (movement.y > 0 && movement.x == 0)
	{
		rightBottomBurner->isVisible = true;
		rightTopBurner->isVisible = true;
	}
	else if (movement.y == 0 && movement.x < 0)
	{
		leftTopBurner->isVisible = true;
		rightTopBurner->isVisible = true;
	}
	else if (movement.y == 0 && movement.x > 0)
	{
		leftBottomBurner->isVisible = true;
		rightBottomBurner->isVisible = true;
	}


	//normalize the movement
	movement.Normalize();
	//Adding the movement to the transform

	float finalVel = velocity * (timePipe->GetDeltaTIme() + 1);
	GetComponent<Collider>().SetVelocity(movement * finalVel);

	GetComponent<Transform>().position = GetComponent<Collider>().GetPosition();


	//Lock the spaceship to the window;
	if (GetComponent<Transform>().position.x < 40)
	{
		GetComponent<Transform>().position.x = 40;
		GetComponent<Collider>().SetPosition(GetComponent<Transform>().position);
	}
	if (GetComponent<Transform>().position.x > 860)
	{
		GetComponent<Transform>().position.x = 860;
		GetComponent<Collider>().SetPosition(GetComponent<Transform>().position);
	}
	if (GetComponent<Transform>().position.y < 35)
	{
		GetComponent<Transform>().position.y = 35;
		GetComponent<Collider>().SetPosition(GetComponent<Transform>().position);
	}
	if (GetComponent<Transform>().position.y > 565)
	{
		GetComponent<Transform>().position.y = 565;
		GetComponent<Collider>().SetPosition(GetComponent<Transform>().position);
	}


	if (unb)
	{
		unbTimer -= 1 + timePipe->GetDeltaTIme();


		if (unbTimer < maxUnbTimer / 4)
		{
			unbAnimation = true;
		}
		else if (unbTimer < maxUnbTimer / 3)
		{

			unbAnimation = false;
		}
		else if (unbTimer < maxUnbTimer / 2)
		{
			unbAnimation = true;
		}
		else if (unbTimer < maxUnbTimer / 1.5)
		{

			unbAnimation = false;
		}

		if (unbTimer <= 0)
		{
			unbTimer = maxUnbTimer;
			GetComponent<Collider>().ActivateCollider();
			unb = false;
			unbAnimation = false;
		}
	}

	if (spaceship->color.x > 10)
	{
		--damageTimer;
	}

	if (damageTimer <= 0)
	{
		spaceship->color = { 1,1,1 };
		damageTimer = 100;
	}

}

void Spaceship::FixUpdate()
{
	Super::FixUpdate();
}

void Spaceship::DecreaseLife(int quantaty)
{
	LifeInterface::DecreaseLife(quantaty);

	spaceship->color = { 100, 100, 100 };

	if (!isAlive)
	{
		--gameLifes;

		if (gameLifes < 0)
		{
			engine->LoadLevel(mainMenu);
		}

		ResetLife();
		unbAnimation = true;
		unb = true;
		GetComponent<Collider>().DisableCollider();
	}

	myHUD->UpdateLife(life);
	myHUD->UpdateSpaceships(gameLifes);
	
}

