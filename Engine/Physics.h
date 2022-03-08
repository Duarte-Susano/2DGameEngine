#pragma once

#include <iostream>
#include <stdio.h>
#include "box2d.h"
#include "ListenerManager.h"
#include "TimePipeline.h"

class Physics
{
public:
	//Get Physics instance
	static Physics* GetPhysics();
	//Destructor
	~Physics();
	//Creates a physics world
	void CreateWorld();
	//Simulates the physics
	void LoopWorldSimulation();

	//returns the world
	b2World* GetWorld();

private:
	//my instance
	static Physics* instance;

	TimePipeline* timepipe;

	//gravity for the world
	b2Vec2 gravity;
	//the world
	b2World* world;

	//time of iterations
	float timeStep;
	int32 velocityIterations;
	int32 positionIterations;

	//reference to ListenerManager
	ListenerManager* myListenerManager;
};