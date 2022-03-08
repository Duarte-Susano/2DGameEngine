#pragma once
#include "box2d.h"


class ListenerManager: public b2ContactListener
{
public:
	//When two colliders collides
	void BeginContact(b2Contact* contact);
};

