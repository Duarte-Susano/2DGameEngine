#pragma once
#include <string>
#include "Object.h"
#include "Level.h"

#include<thread>


class GameEngine
{
public:
	//returns instance of the game engine
	static GameEngine* GetGameEngine();

	//initialize variables
	void Init(std::string windowTitle, int windowWidth, int windowHeight);
	
	//loadLevelToUpdate
	void LoadLevel(Level* levelToLoad);

	//Returns current level
	Level* GetCurrentLevel();

	//Loop the game
	void RunEngine();

	//void FixedUpdate();

	//destructor
	~GameEngine();

private:

	//instance of Game Engine
	static GameEngine* instance;
	//the current level
	Level* loadedLevel{ nullptr };
	//reference to Render Manager
	class RenderManager* renderManager{ nullptr };
	//reference to SDL Wrapper
	class SDLWrapper* sdl{ nullptr };
	//reference to Window
	class Window* window{ nullptr };
	//reference to Time Pipeline
	class TimePipeline* timePipe{};
	//reference to Input Manager
	class InputManager* inputManager{};
	//reference to Physics
	class Physics* physicsManager;
	//reference to Sound Manager
	class SoundManager* mySoundManager;

	bool isRunning = true;
	bool fixUpdateBlocker = true;
};

