#pragma once
#include <iostream>
#include "Component.h"

struct Sound: public Component
{
	void PlaySound(std::string file);

	bool soundPlay = false;
	std::string filePath = "";
};

