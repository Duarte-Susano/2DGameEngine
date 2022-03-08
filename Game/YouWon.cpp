#include "YouWon.h"

void YouWon::Construct()
{
	Super::Construct();
	AddComponent<Text>("You Won!", 2, 0, 0, 0);
}

void YouWon::Start()
{
	Super::Start();
	GetComponent<Transform>().position = { 350, 300,0 };
}
