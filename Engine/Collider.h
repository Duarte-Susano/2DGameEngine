#pragma once
#include "Component.h"
#include "Vector3.h"
#include <iostream>
class Collider : public Component
{
public:

	Collider();

	~Collider();

	//type of collider
	enum ColliderType {StaticBody, KinematicBody, DynamicBody};

	//Associates a collider
	void MakeCollider(
	Vector3 objectposition,
	ColliderType myType,
	float sizeX,
	float sizeY,
	float speedX,
	float speedY,
	float gravity,
	bool isTrigger,
	bool isBullet);

	//Sets the position of the collider
	void SetPosition(Vector3 newPosition);

	//Sets the velocity of the collider
	void SetVelocity(Vector3 newVelocity);

	//Gets thr current position
	Vector3 GetPosition();

	//is call when a collision occours
	void OnCollision(Object* otherObject);

	//disables the collider
	void DisableCollider();

	//activates the collider
	void ActivateCollider();

	//Returns is active
	bool GetIsActive();

	//acess for collider type
	ColliderType myColliderType;

	//if as collide
	bool asCollided = false;

	//Returns the object with wich collide
	Object* GetCollisionResultObject();

private: 

	//layers for filter
	struct Layers
	{
		short Layer_Default = 0x0001;
		short Layer_Disabled = 0x0001;

		short Mask_Default = ~Mask_Disabled;
		short Mask_Disabled = Layer_Default | Layer_Disabled;
	};
	//my layers
	Layers layers;

	//if the collider is active
	bool isActive = true;

	//The object with wich collide
	Object* collisionResultOject = nullptr;
	//Check for the collisionResultObject
	bool otherObjectValid = true;

	//collider body defenition
	class b2BodyDef* myColliderBodyDef = nullptr;

	//collider body
	class b2Body* colliderBody = nullptr;

	//collider sizes
	int collW;
	int collH;

	//class b2BodyDef* bodyDef {};
	class b2PolygonShape* dynamicBox{nullptr};
	//class b2FixtureDef* fixtureDef{};
	class b2World* myWorld{nullptr};

	//my physics manager
	class Physics* physicsManager{nullptr};
	//Sets a physic world
	void SetPhysicsWorld();

	void Update() override;
};

