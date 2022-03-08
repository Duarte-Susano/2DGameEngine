#include "BackgroundParalax.h"

void BackgroundParalax::Construct()
{
	Super::Construct();
	//Adds an image
	image1 = AddComponent<Image>("XenonImages/Background.bmp", 1, 1, -2);
	image2 = image1 = AddComponent<Image>("XenonImages/Background.bmp", 1, 1, -2);
	image2->xOffSet = 900;
}

void BackgroundParalax::Start()
{
	Super::Start();
	//Sets the initial position
	GetComponent<Transform>().position = {450,300,0};
}

void BackgroundParalax::Update()
{
	Super::Update();

	GetComponent<Transform>().position.x -= 0.1;

	// puts the object down
	if (GetComponent<Transform>().position.x <= -450)
	{
		GetComponent<Transform>().position.x = 450;
	}
}
