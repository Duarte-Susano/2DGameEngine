#include "Physics.h"
#include <stdio.h>


Physics* Physics::GetPhysics()
{
	if (instance == nullptr)
		instance = new Physics;
	return instance;
}

Physics::~Physics()
{
	delete world;
	delete myListenerManager;
}

void Physics::CreateWorld()
{	
	gravity.Set(0.0f, -9.81f);
	world = new b2World(gravity);
	timeStep = (1.0f / 60.0f);
	velocityIterations = 6;
	positionIterations = 2;

	timepipe = timepipe->GetTimePipelineInstance();

	if (myListenerManager == nullptr)
	{
		myListenerManager = new ListenerManager;
	}

	world->SetContactListener(myListenerManager);
}

void Physics::LoopWorldSimulation()
{
	// Instruct the world to perform a single step of simulation.
	// It is generally best to keep the time step and iterations fixed.

	world->Step(timeStep, velocityIterations, positionIterations);

	// Now print the position and angle of the body.
	
}

b2World* Physics::GetWorld()
{
	return world;
}


