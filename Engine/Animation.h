#pragma once
#include <iostream>



class Animation
{
public:
	Animation(){}
	~Animation() {}
	//simple animation
	Animation(int rhsStartFrame, int rhsEndFrame, float rhsVelocity, bool rhsLoop);
	//animation with changing image
	Animation(std::string newImage, int newNColumns, int newNRows, int rhsStartFrame, int rhsEndFrame, float rhsVelocity, bool rhsLoop);


	bool operator==(const Animation& other) const;
	bool operator!=(const Animation& other) const;

	//animation with changing image parameters
	std::string newFilePath = "";
	int nColumns = 1;
	int nRows = 1;

	//simple animation
	int startFrame = 0;
	int endFrame = 0;
	float velocity = 1.0f;
	bool loop = false;
};

