#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"
#include "RenderManager.h"
#include "TimePipeline.h"
#include "InputManager.h"
#include "Physics.h"
#include "SoundManager.h"



//Initialize instances
GameEngine* GameEngine::instance = 0;
TimePipeline* TimePipeline::instance = 0;
InputManager* InputManager::instance = 0;
Physics* Physics::instance = 0;
RenderManager* RenderManager::instance = 0;


//Get instance of game engine
GameEngine* GameEngine::GetGameEngine()
{
	if(!instance)
	instance = new GameEngine;
	return instance;
}

//Initialize variables
void GameEngine::Init(std::string windowTitle, int windowWidth, int windowHeight)
{
	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK);
	window = new Window(windowTitle, windowWidth, windowHeight);
	renderManager->CreateRendermanager(window->GetWindow());
	renderManager = renderManager->GetRenderManager();
	//renderManager = new RenderManager(window->GetWindow());
	timePipe = timePipe->GetTimePipelineInstance();
	inputManager = inputManager->GetInputManager();
	inputManager->HandleInputsGamepad();
	mySoundManager = new SoundManager();
	physicsManager = physicsManager->GetPhysics();
	physicsManager->CreateWorld();
}

void GameEngine::LoadLevel(Level* levelToLoad)
{
	loadedLevel = levelToLoad;
	loadedLevel->StartObjects();
}

Level* GameEngine::GetCurrentLevel()
{
	return loadedLevel;
}


void GameEngine::RunEngine()
{
	SDL_Event ev;


	if (loadedLevel != nullptr)
	{	

		while (isRunning)
		{
			//load unitializeObject
			loadedLevel->RefreshLevel();


			//inputs:
			while (SDL_PollEvent(&ev) != 0)
			{
				if (ev.type == SDL_QUIT)
					isRunning = false;

				inputManager->InputsGamePadLoop(ev);
			}
			inputManager->HandleInputsKeyboard();

			//Update Objects
			loadedLevel->UpdateObjects();

			//Render
			renderManager->RenderObjects(loadedLevel->GetObjectsInList());

			mySoundManager->SpawnSounds(loadedLevel->GetObjectsInList());

			window->updateSurface();
			loadedLevel->FixUpdateObjects();

			timePipe->UpdateTime();
			fixUpdateBlocker = false;


			//Update physics
			physicsManager->LoopWorldSimulation();
		}
	}
	else
	{
		throw std::runtime_error("No level loaded");
	}


}


GameEngine::~GameEngine()
{
	delete window;
	delete sdl;
	delete renderManager;
	delete timePipe;
	delete inputManager;
	delete physicsManager;
}
