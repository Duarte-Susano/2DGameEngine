#include "Level.h"
#include <algorithm>

Level::Level()
{
}

Level::~Level()
{
	objectsList.clear();
	numberOfObjects = 0;
}

void Level::EmptyLevel()
{
	for (Object* obj : objectsList)
	{
		delete(obj);
	}
}

void Level::AddObject(Object* obj)
{
	objectsList.emplace_back(obj);
	obj->Construct();
}


void Level::RemoveObject(Object* obj)
{
	objectsList.erase(std::remove(objectsList.begin(), objectsList.end(), obj));
	delete(obj);
}


void Level::SpawnObject(Object* obj)
{
	unitializedObjects.push_back(obj);
}

void Level::RefreshLevel()
{
	//Removing objects
	std::vector<Object*> deletingObjects;

	for (int i = 0; i < objectsList.size(); ++i)
	{
		if (objectsList[i]->pendingDestroy)
		{
			deletingObjects.push_back(objectsList[i]);
		}
	}

	for (int i = 0; i < deletingObjects.size(); ++i)
	{
		RemoveObject(deletingObjects[i]);
	}

	//Initialize objects
	for (int i = 0; i < unitializedObjects.size(); ++i)
	{
		AddObject(unitializedObjects[i]);
		unitializedObjects[i]->Start();
	}
	unitializedObjects.clear();
}

void Level::ConstructObjects()
{
	for (int i = 0; i < objectsList.size(); ++i)
	{
		objectsList[i]->Construct();
	}
}

void Level::StartObjects()
{
	for (int i = 0; i < objectsList.size(); ++i)
	{
		objectsList[i]->Start();
	}
}

void Level::UpdateObjects()
{	
	for ( int i = 0; i < objectsList.size(); ++i)
	{
		objectsList[i]->Update();
	}
}

void Level::FixUpdateObjects()
{
}

std::vector<Object*> Level::GetObjectsInList()
{
	return objectsList;
}
