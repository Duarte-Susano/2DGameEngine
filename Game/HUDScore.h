#pragma once
#include "Object.h"
#include <fstream> 
#include <string>

class HUDScore: public Object
{
public:
	void AddScore(int quantaty);
	
private:
	
	int playerScore = 0;
	int highScore = 0;
	Text* playerScoreText = nullptr;
	Text* highScoreText = nullptr;
	using Super = Object;
	void Construct() override;
	void Start() override;
};

