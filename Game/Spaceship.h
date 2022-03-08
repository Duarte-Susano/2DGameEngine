#pragma once
#include "ControllableCharacter.h"
#include "LifeInterface.h"
#include "ShooterMissilesInterface.h"

#include <iostream>
#include <vector>

#include "Level.h"
#include "Missile.h"
#include "TimePipeline.h"
#include "HUDLife.h"

#include "GameEngine.h"

class Spaceship:   public ControllableCharacter, public LifeInterface, public ShooterMissilesInterface
{
	using Super = ControllableCharacter;

public:
	Spaceship(Level* level, GameEngine* gameEngine, Level* mainMenuLevel, HUDLife* hudLife):
	myLevel{ level }, engine{gameEngine}, mainMenu{mainMenuLevel}, myHUD{hudLife} {};

	~Spaceship();

	void SpawnCompanion();

	void AddLife(int quantaty);
	void AddGameLifes(int quantaty);

	bool companionLeft = false;
	bool companionRight = false;

protected:
	GameEngine* engine = nullptr;
	Level* mainMenu = nullptr;
	HUDLife* myHUD = nullptr;
	Level* myLevel = nullptr;
	Sound* mySound = nullptr;
	int damageTimer = 100;
	int wLimit = 1000;
	int hLimit = 1000;
	int gameLifes = 2;
	bool firstShoot = false;
	bool shooting = false;
	bool unbAnimation = true;
	bool unb = true;
	float unbTimer = 1000.f;
	float maxUnbTimer = 2000.f;
	float timeToShoot = 10.0f;
	float shootTime = 0.0f;
	float velocity = 20.0f;


	Vector3 movement = {0,0,0};

	//Animations
	Animation idle = {4, 4, 1, true};
	Animation turningLeft = {4, 1, 3, false};
	Animation leftToCenter = {1, 4, 3, false};
	Animation turningRight = {4, 7, 3, false};
	Animation rightToCenter = {7, 4, 3, false};

	Animation unbIdle = { 11, 11, 1, true };
	Animation unbTurningLeft = { 11, 8, 3, false };
	Animation unbLeftToCenter = { 8, 11, 3, false };
	Animation unbTurningRight = { 11, 14, 3, false };
	Animation unbRightToCenter = { 14, 11, 3, false };

	Image* spaceship = nullptr;
	Image* mainBurner = nullptr;
	Image* leftBottomBurner = nullptr;
	Image* rightBottomBurner = nullptr;
	Image* leftTopBurner = nullptr;
	Image* rightTopBurner = nullptr;

	TimePipeline* timePipe;

	void Construct() override;
	void Start() override;
	void Update() override;
	void FixUpdate() override;
	void DecreaseLife(int quantaty) override;
	
};

