#include <iostream>
#include "Collider.h"
#include "Object.h"
#include "box2d.h"
#include "Physics.h"

#include <string>


Collider::Collider()
{
}

Collider::~Collider()
{
	if (colliderBody != nullptr)
	{
		myWorld->DestroyBody(colliderBody);

	}
	if (myColliderBodyDef != nullptr)
	{
		delete myColliderBodyDef;
	}
	if (dynamicBox != nullptr)
	{
		delete dynamicBox;
	}
}


void Collider::SetPhysicsWorld()
{
	physicsManager = physicsManager->GetPhysics();
	myWorld = physicsManager->GetWorld();

}

void Collider::OnCollision(Object* otherObject)
{
	otherObjectValid = true;
	asCollided = true;
	collisionResultOject = otherObject;
}

void Collider::DisableCollider()
{
	b2Filter filter;
	filter.categoryBits = layers.Layer_Disabled;
	filter.maskBits = layers.Mask_Disabled;

	colliderBody->GetFixtureList()->SetFilterData(filter);
	isActive = false;
}

void Collider::ActivateCollider()
{
	b2Filter filter;
	filter.categoryBits = layers.Layer_Default;
	filter.maskBits = layers.Mask_Default;
	colliderBody->GetFixtureList()->SetFilterData(filter);
	isActive = true;
}

bool Collider::GetIsActive()
{
	return isActive;
}


Object* Collider::GetCollisionResultObject()
{
	if (collisionResultOject != nullptr)
	{
		return collisionResultOject;
	}
	return nullptr;
}

void Collider::Update()
{
	if (isActive)
	{
		if (collisionResultOject != nullptr)
		{
			if (!collisionResultOject->isActive
				|| collisionResultOject->pendingDestroy)
			{
				collisionResultOject = nullptr;
			}
		}
	}
	
}


void Collider::MakeCollider(
	Vector3 objectposition,
	ColliderType myType,
	float sizeX,
	float sizeY,
	float speedX,
	float speedY,
	float gravity,
	bool isTrigger,
	bool isBullet)
{
	myColliderBodyDef = new b2BodyDef;
	b2FixtureDef* myFixtureDef = new b2FixtureDef;
	b2Vec2 mySpeed;

	float Xspeed = 0;

	float Yspeed = 0;

	Xspeed = speedX;
	Yspeed = -speedY;

	mySpeed.Set(Xspeed, Yspeed);

	SetPhysicsWorld();

	dynamicBox = new b2PolygonShape;

	myColliderBodyDef->bullet = isBullet;
	myColliderBodyDef->position.Set(objectposition.x, objectposition.y);
	myColliderBodyDef->userData.pointer = (uintptr_t)this;

	switch (myType)
	{
	case StaticBody:
		myColliderBodyDef->type = b2_staticBody;
		myColliderType = StaticBody;
		break;

	case KinematicBody:
		myColliderBodyDef->type = b2_kinematicBody;
		myColliderType = KinematicBody;
		break;

	case DynamicBody:
		myColliderBodyDef->type = b2_dynamicBody;
		myColliderType = DynamicBody;
		break;
	}


	colliderBody = myWorld->CreateBody(myColliderBodyDef); //body = GameEngine::getInstance()->getWorld()->CreateBody(&bodyDef);


	dynamicBox->SetAsBox(sizeX * myObject->GetComponent<Transform>().scale.x / 2,
	sizeY * myObject->GetComponent<Transform>().scale.y / 2); 


	myFixtureDef->shape = dynamicBox;
	myFixtureDef->density = 1.0f;
	myFixtureDef->isSensor = isTrigger;

	colliderBody->CreateFixture(myFixtureDef);

	colliderBody->SetLinearVelocity(mySpeed);

	colliderBody->SetGravityScale(gravity);

}

void Collider::SetPosition(Vector3 newPosition)
{
	b2Vec2 newPos;
	newPos.x = newPosition.x;
	newPos.y = newPosition.y;
	colliderBody->SetTransform(newPos,0.0f);
}

void Collider::SetVelocity(Vector3 newVelocity)
{
	b2Vec2 newVel;
	newVel.x = newVelocity.x;
	newVel.y = newVelocity.y;
	colliderBody->SetLinearVelocity(newVel);
}

Vector3 Collider::GetPosition()
{
	if (this != nullptr)
	{
		Vector3 returnPosition;
		b2Vec2 bodyPos;
		bodyPos = colliderBody->GetPosition();

		returnPosition.x = bodyPos.x;
		returnPosition.y = bodyPos.y;

		return returnPosition;
	}
	Vector3 VError = { 0 ,0,0};
	return VError;
}
