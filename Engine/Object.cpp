#include "Object.h"
#include <iostream>

Object::~Object()
{
	DestroyComponents();
	parent = nullptr;
}

void Object::Construct()
{
	for (auto& comp : components)
	{
		comp->Construct();
	}

	AddComponent<Transform>();
}

void Object::Start()
{
	for (auto& comp : components)
	{
		comp->Start();
	}
	GetComponent<Transform>().parent = parent;
}

void Object::Update()
{
	if (!pendingDestroy)
	{
		for (auto& comp : components)
		{
			comp->Update();
		}
	}
}

void Object::FixUpdate()
{
	if (!pendingDestroy)
	{
		for (auto& comp : components)
		{
			comp->FixUpdate();
		}
	}
}

void Object::SetParent(Transform* parentTransform)
{
	parent = parentTransform;
}

void Object::Destroy(Object* obj)
{
	obj->isActive = false;
	obj->pendingDestroy = true;
}

void Object::SetTag(std::string newTag)
{
	myTag = newTag;

}

std::string Object::GetTag()
{
	return myTag;
}

void Object::DestroyComponents()
{
	for (auto& comp : components)
	{
		delete(comp);
	}
}
