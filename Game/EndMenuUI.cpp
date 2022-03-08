#include "EndMenuUI.h"

void EndMenuUI::Construct()
{
	Super::Construct();
	AddComponent<Text>("Game Over", 2, 0,0,0);
}

void EndMenuUI::Start()
{
	Super::Start();
	GetComponent<Transform>().position = {350, 300,0};
}
