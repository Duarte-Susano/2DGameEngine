#pragma once
#include "Object.h"
#include "Vector3.h"
#include "Level.h"

class EnemyAttack: public Object
{
	using Super = Object;

public:

	EnemyAttack(Vector3 initialPosition, Vector3 direction, Level* rhsMylevel) :myInitialPosition{ initialPosition },
		myLevel{ rhsMylevel },
		myDirection{ direction }
	{}

	~EnemyAttack();

protected:

	Level* myLevel = nullptr;
	Vector3 myInitialPosition = {};
	Vector3 myDirection = {};
	Animation idle = { 1, 8, 1, true };

	float velocity = 20.0f;

	//Object functions
	void Construct() override;
	void Start() override;
	void Update() override;

};

