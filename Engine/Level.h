#pragma once
#include "Object.h"
#include <iostream>
#include <vector>


class Level
{
public:
	Level();
	~Level();

	//add an object to the level
	void AddObject(Object* obj);

	//removes an object from the level
	void RemoveObject(Object* obj);

	//spawns an object
	void SpawnObject(Object* obj);

	//creates and deletes holding objects
	void RefreshLevel();

	//calls BeginPlay function of every object in the level
	void ConstructObjects();

	//calls Start function of every object in the level
	void StartObjects();

	//calls update function of every object in the level
	void UpdateObjects();

	void EmptyLevel();

	//calls fixupdate function of every object in the level
	void FixUpdateObjects();

	std::vector<Object*> GetObjectsInList();

private:
	//capacity of the level | it changes dynamicaly
	int capacity = 50;

	//counter of objects in the level
	int numberOfObjects = 0;

	//array of objects in the level
	std::vector<Object*> objectsList;

	//array of object to initialize
	std::vector<Object*> unitializedObjects;
};

