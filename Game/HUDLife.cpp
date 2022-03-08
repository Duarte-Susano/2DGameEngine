#include "HUDLife.h"

void HUDLife::UpdateLife(int newLife)
{
	switch (newLife)
	{
	case 0:
		for (int i = 0; i < 10; ++i)
		{
			lifes[i]->isVisible = false;
		}
		break;
	case 1:
		lifes[0]->isVisible = true;
		for (int i = 1; i < 10; ++i)
		{
			lifes[i]->isVisible = false;
			lifes[i]->color = { 1,0,0 };
		}
		for (int i = 0; i < 10; ++i)
		{
			lifes[i]->color = { 1,0,0 };
		}
		break;
	case 2:
		for (int i = 0; i < 1; ++i)
		{
			lifes[i]->isVisible = true;
			lifes[i]->color = { 1,0,0 };
		}
		for (int i = 2; i < 10; ++i)
		{
			lifes[i]->isVisible = false;
			lifes[i]->color = { 1,0,0 };
		}
		for (int i = 0; i < 10; ++i)
		{
			lifes[i]->color = { 1,0,0 };
		}
		break;
	case 3:
		for (int i = 0; i < 2; ++i)
		{
			lifes[i]->isVisible = true;
			lifes[i]->color = { 1,0,0 };
		}
		for (int i = 3; i < 10; ++i)
		{
			lifes[i]->isVisible = false;
			lifes[i]->color = { 1,0,0 };
		}
		for (int i = 0; i < 10; ++i)
		{
			lifes[i]->color = { 1,0,0 };
		}
		break;
	case 4:
		for (int i = 0; i < 3; ++i)
		{
			lifes[i]->isVisible = true;
		}
		for (int i = 4; i < 10; ++i)
		{
			lifes[i]->isVisible = false;
		}
		for (int i = 0; i < 10; ++i)
		{
			lifes[i]->color = { 1,1,0 };
		}
		break;
	case 5:
		for (int i = 0; i < 4; ++i)
		{
			lifes[i]->isVisible = true;
		}
		for (int i = 5; i < 10; ++i)
		{
			lifes[i]->isVisible = false;
		}
		for (int i = 0; i < 10; ++i)
		{
			lifes[i]->color = { 1,1,0 };
		}
		break;
	case 6:
		for (int i = 0; i < 5; ++i)
		{
			lifes[i]->isVisible = true;
		}
		for (int i = 6; i < 10; ++i)
		{
			lifes[i]->isVisible = false;
		}
		for (int i = 0; i < 10; ++i)
		{
			lifes[i]->color = { 1,1,0 };
		}
		break;
	case 7:
		for (int i = 0; i < 6; ++i)
		{
			lifes[i]->isVisible = true;
		}
		for (int i = 7; i < 10; ++i)
		{
			lifes[i]->isVisible = false;
		}
		for (int i = 0; i < 10; ++i)
		{
			lifes[i]->color = { 1,1,0 };
		}
		break;
	case 8:
		for (int i = 0; i < 7; ++i)
		{
			lifes[i]->isVisible = true;
		}
		for (int i = 8; i < 10; ++i)
		{
			lifes[i]->isVisible = false;
		}
		for (int i = 0; i < 10; ++i)
		{
			lifes[i]->color = { 0,1,0 };
		}
		break;
	case 9:
		for (int i = 0; i < 8; ++i)
		{
			lifes[i]->isVisible = true;
		}
		lifes[9]->isVisible = false;
		for (int i = 0; i < 10; ++i)
		{
			lifes[i]->color = { 0,1,0 };
		}
		break;
	case 10:
		for (int i = 0; i < 10; ++i)
		{
			lifes[i]->isVisible = true;
		}
		for (int i = 0; i < 10; ++i)
		{
			lifes[i]->color = { 0,1,0 };
		}
		break;

	default:
		break;
	}
}

void HUDLife::UpdateSpaceships(int newSpaceships)
{
	switch (newSpaceships)
	{
	case 0:
		spaceship1->isVisible = false;
		spaceship2->isVisible = false;
		spaceship3->isVisible = false;
		break;
	case 1:
		spaceship1->isVisible = true;
		spaceship2->isVisible = false;
		spaceship3->isVisible = false;
		break;
	case 2:
		spaceship1->isVisible = true;
		spaceship2->isVisible = true;
		spaceship3->isVisible = false;
		break;
	case 3:
		spaceship1->isVisible = true;
		spaceship2->isVisible = true;
		spaceship3->isVisible = true;
		break;
	default:
		break;
	}

}

void HUDLife::Construct()
{
	Super::Construct();

	lifeBox = AddComponent<Image>("XenonImages/UILifeBox.bmp", 1, 1, 10);
	lifes[0] = life1 = AddComponent<Image>("XenonImages/UILife1.bmp", 1, 1, 10);
	lifes[1] = life2 = AddComponent<Image>("XenonImages/UILife2.bmp", 1, 1, 10);
	lifes[2] = life3 = AddComponent<Image>("XenonImages/UILife3.bmp", 1, 1, 10);
	lifes[3] = life4 = AddComponent<Image>("XenonImages/UILife4.bmp", 1, 1, 10);
	lifes[4] = life5 = AddComponent<Image>("XenonImages/UILife5.bmp", 1, 1, 10);
	lifes[5] = life6 = AddComponent<Image>("XenonImages/UILife6.bmp", 1, 1, 10);
	lifes[6] = life7 = AddComponent<Image>("XenonImages/UILife7.bmp", 1, 1, 10);
	lifes[7] = life8 = AddComponent<Image>("XenonImages/UILife8.bmp", 1, 1, 10);
	lifes[8] = life9 = AddComponent<Image>("XenonImages/UILife9.bmp", 1, 1, 10);
	lifes[9] = life10 = AddComponent<Image>("XenonImages/UILife10.bmp", 1, 1, 10);

	spaceship1 = AddComponent<Image>("XenonImages/Ship2.bmp", 7, 3, 10);
	spaceship1->PlayAnimation(spaceshipPos);
	spaceship1->yOffSet = 50;
	spaceship1->xOffSet = -50;
	spaceship2 = AddComponent<Image>("XenonImages/Ship2.bmp", 7, 3, 10);
	spaceship2->PlayAnimation(spaceshipPos);
	spaceship2->yOffSet = 50;
	spaceship3 = AddComponent<Image>("XenonImages/Ship2.bmp", 7, 3, 10);
	spaceship3->PlayAnimation(spaceshipPos);
	spaceship3->yOffSet = 50;
	spaceship3->xOffSet = 50;


}

void HUDLife::Start()
{
	Super::Start();
	GetComponent<Transform>().position = {100, 20, 0};
	GetComponent<Transform>().scale = {0.7f,0.7f,0.0f};

	UpdateLife(10);
}

void HUDLife::Update()
{
	Super::Update();
}
