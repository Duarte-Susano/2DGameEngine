#pragma once
#include "Vector3.h"
#include "Component.h"

struct Transform : public Component
{
	Vector3 position {0,0,0};
	Vector3 rotation {0,0,0};
	Vector3 scale {1,1,1};

	Vector3 velocity {0,0,0};

	Transform* parent = nullptr;
}; 

