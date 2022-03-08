#include "MainMenuUI.h"
#include <iostream>


MainMenuUI::~MainMenuUI()
{
}


void MainMenuUI::Construct()
{
	Super::Construct();
	AddComponent<Text>("Press Start", 2, 0, 0, 0);
}

void MainMenuUI::Start()
{
	Super::Start();
	GetComponent<Transform>().position = {350, 300, 0};
	startGame = false;
}

void MainMenuUI::Update()
{
	Super::Update();

	if (inputs.SPACE && !startGame)
	{
		startGame = true;
		if (myEngine != nullptr)
		{
			myEngine->LoadLevel(myLevel);
		}
		else
		{
			std::cout << "no Loaded Level" << std::endl;
		}
	}
}


