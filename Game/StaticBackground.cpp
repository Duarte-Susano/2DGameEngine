#include "StaticBackground.h"

void StaticBackground::Construct()
{
	Super::Construct();

	AddComponent<Image>("XenonImages/galaxy2.bmp", 1, 1, -3);
}

void StaticBackground::Start()
{
	Super::Start();

	GetComponent<Image>().fullScreen = true;
}

