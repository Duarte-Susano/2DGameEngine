#include "ListenerManager.h"
#include <iostream>
#include "Collider.h"
#include "Object.h"

void ListenerManager::BeginContact(b2Contact* contact)
{
	Collider* firstCollider = nullptr;
	Collider* secondCollider = nullptr;

	void* userData = (void*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	if (userData)
	{
		firstCollider = static_cast<Collider*>(userData);
	}
	void* userDataB = (void*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
	if (userDataB)
	{
		secondCollider = static_cast<Collider*>(userDataB);
	}

	//Calls OnCollision of each collider and send the opposite Object
	if (firstCollider->GetIsActive() && secondCollider->GetIsActive())
	{
		if (firstCollider != nullptr && secondCollider != nullptr)
		{
			if (firstCollider->myObject != nullptr && secondCollider->myObject != nullptr)
			{
				firstCollider->OnCollision(secondCollider->myObject);
				secondCollider->OnCollision(firstCollider->myObject);
			}
		}
	}

	firstCollider = nullptr;
	secondCollider = nullptr;
}
