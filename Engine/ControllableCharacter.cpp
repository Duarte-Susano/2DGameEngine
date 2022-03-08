#include "ControllableCharacter.h"

void ControllableCharacter::Construct()
{
	Object::Construct();
	AddComponent<Controller>();
}

void ControllableCharacter::Start()
{
	Object::Start();
}

void ControllableCharacter::Update()
{
	Object::Update();
	inputs = GetComponent<Controller>().inputs;
}
