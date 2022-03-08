#include "HUDScore.h"


void HUDScore::AddScore(int quantaty)
{
	playerScore += quantaty;
	if (playerScore > 999999999)
	{
		playerScore = 999999999;
	}

	if (playerScore > highScore)
	{
		highScore = playerScore;
		highScoreText->text = std::to_string(highScore);

		std::ofstream outFile("highScore.txt");

		outFile << highScore << std::endl;

		outFile.close();
	}

	playerScoreText->text = std::to_string(playerScore);
}

void HUDScore::Construct()
{
	Super::Construct();

	AddComponent<Text>("Player One", 1, 0, 0, 10);
	playerScoreText = AddComponent<Text>(std::to_string(playerScore), 1, 0, -22, 10);

	AddComponent<Text>("High Score", 0.7, 400, 0, 10);

	std::fstream fileStream;

	fileStream.open("highScore.txt", std::ios::in);
	if (fileStream.fail()) {
		
	}
	else
	{
		fileStream >> highScore;
	}

	fileStream.close();

	highScoreText = AddComponent<Text>(std::to_string(highScore), 0.7, 400, -15, 10);

}

void HUDScore::Start()
{
	Super::Start();

	GetComponent<Transform>().position = {10,570,0};

}