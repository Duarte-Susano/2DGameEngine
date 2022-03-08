#pragma once
#include <iostream>
#include "Component.h"

struct Text : public Component
{
	Text(){};
	Text(std::string textToRender, float rhsSize, float rhsXOffSet, float rhsYOffSet, int rhsLayer);

	std::string text = "";
	float size = 1.0f;
	float xOffSet = 0.0f;
	float yOffSet = 0.0f;
	int layer = 0;
	bool isVisible = true;
};

