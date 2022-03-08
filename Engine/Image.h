#pragma once
#include <iostream>
#include "Component.h"
#include "Animation.h"
#include "Vector3.h"

struct Image : public Component
{

	//Constructor
	Image();
	Image(std::string rhsFilePath, int rhsNColumns, int rhsNRows, int rhsLayer);
	//Destructor
	~Image();

	//order of priority of render
	int layer = 0;
	//filepath to the image
	std::string filePath = "";
	//nº of rows of the intended image
	int nRows = 1;
	//nº of columns of the intended image
	int nColumns = 1;
	//position of the intended frame
	int framePositionRow = 1;
	int framePositionColumn = 1;
	//if is ocupie the entire screen
	bool fullScreen = false;
	//if flip image horizontaly
	bool flipImageHorizontal = false;
	//if flip image verticaly
	bool flipImageVertical = false;

	bool isVisible = true;

	Vector3 color = {1,1,1};

	float xOffSet = 0;
	float yOffSet = 0;

	//sizes of the image
	int imageWidth = 100;
	int imageHeight = 100;
	//Get Image Size
	void GetImageSizes();

	//Plays a new animation
	void PlayAnimation(Animation rhsAnimationToPlay);
	//Returns the current animation
	Animation GetCurrentAnimation();
	//Returns true when the animation ends
	bool EndOfAnimation();
	//Stops the animation
	void StopAnimation();

private:
	void Start() override;
	void Update() override;

	//Reference to the Render Manager
	class RenderManager* myRenderManager = nullptr;
	//the current animation
	Animation animationToPlay;
	//if is playing an animation
	bool playingAnimation = false;
	//triggers when the animation ends
	bool endOfAnimation = false;
	//timer
	float frameTime = 0.0f;
	//reference to the Time Pipeline
	class TimePipeline* timePipe {};
	//counter of the animation
	int currentFrame = 0;
	//the imageSize

};

