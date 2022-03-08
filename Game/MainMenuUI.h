#pragma once
#include "ControllableCharacter.h"
#include "Object.h"
#include "Level.h"
#include "GameEngine.h"

class MainMenuUI : public ControllableCharacter
{

	using Super = ControllableCharacter;

public:

	MainMenuUI(Level* level, GameEngine* engine) : myLevel{ level }, myEngine{ engine } {};
	~MainMenuUI();

protected:
	void Construct() override;
	void Start() override;
	void Update() override;

private:

	bool startGame = false;
	Level* myLevel;
	GameEngine* myEngine;

};