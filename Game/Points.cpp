#include "Points.h"


Points::Points(Vector3 initialPosition, int pointsQuantaty)
{
	iniPos = initialPosition;
	points = pointsQuantaty;
}

void Points::Construct()
{
	Super::Construct();

	AddComponent<Text>(std::to_string(points), 0.7, 0, 0, 10);
}

void Points::Start()
{
	Super::Start();

	GetComponent<Transform>().position = iniPos;

}

void Points::Update()
{
	Super::Update();

	GetComponent<Transform>().position.y += velocity;
	--lifeTimer;

	if (lifeTimer <= 0)
	{
		Destroy(this);
	}
}
