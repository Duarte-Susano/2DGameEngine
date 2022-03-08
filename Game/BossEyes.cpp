#include "BossEyes.h"
#include "Points.h"

BossEyes::BossEyes(Vector3 initialPosition, Level* rhsMylevel, BossEye type, HUDScore* myHUD, BossEnemy* myBoss)
{
	realLocation = initialPosition;
	myLevel = rhsMylevel;
	hud = myHUD;
	boss = myBoss;

	switch (type)
	{
	case LeftEye1:
		EyeAnimation = EyeLeft1Anim;
		break;
	case LeftEye2:
		EyeAnimation = EyeLeft2Anim;
		break;
	case LeftEye3:
		EyeAnimation = EyeLeft3Anim;
		break;
	case RightEye1:
		EyeAnimation = EyeRight1Anim;
		break;
	case RightEye2:
		EyeAnimation = EyeRight2Anim;
		break;
	case RightEye3:
		EyeAnimation = EyeRight3Anim;
		break;

	}


}

BossEyes::~BossEyes()
{
	myLevel = nullptr;
	hud = nullptr;
	myImageEye = nullptr;
}


void BossEyes::Construct()
{
	Super::Construct();

	myImageEye = AddComponent<Image>("XenonImages/bosseyes2.bmp", 3, 6, 0);
	AddComponent<Collider>();
}

void BossEyes::Start()
{
	Super::Start();

	SetTag("BossEyes");

	GetComponent<Transform>().position = realLocation;
	GetComponent<Transform>().scale = Vector3{1.5f,1.5f,1.f};
	GetComponent<Transform>().rotation = Vector3{0,0,-90};

	myImageEye->PlayAnimation(EyeAnimation);

	GetComponent<Collider>().MakeCollider(
		GetComponent<Transform>().position,
		GetComponent<Collider>().DynamicBody,
		myImageEye->imageWidth / myImageEye->nColumns,
		myImageEye->imageHeight / myImageEye->nRows,
		0.0f,
		0.0f,
		0.0f,
		true,
		true);

	life = 20;

}

void BossEyes::Update()
{
	Super::Update();

	if (isDead)
	{
		Destroy(this);
	}

	if (myImageEye->color.x > 10)
	{
		--damageTimer;
	}

	if (damageTimer <= 0)
	{
		myImageEye->color = { 1,1,1 };
		damageTimer = 100;
	}

}

void BossEyes::DecreaseLife(int quantaty)
{
	LifeInterface::DecreaseLife(quantaty);

	myImageEye->color = { 100, 100, 100 };

	if (!isAlive)
	{
		myLevel->SpawnObject(new Points(GetComponent<Transform>().position, score));
		hud->AddScore(score);
		boss->EyeDied();
		isDead = true;
	}
}
