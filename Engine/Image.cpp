#include "Image.h"
#include "TimePipeline.h"
#include "RenderManager.h"

Image::Image()
{
	myRenderManager = myRenderManager->GetRenderManager();
	timePipe = timePipe->GetTimePipelineInstance();
}

Image::Image(std::string rhsFilePath, int rhsNColumns, int rhsNRows, int rhsLayer)
{
	myRenderManager = myRenderManager->GetRenderManager();
	timePipe = timePipe->GetTimePipelineInstance();

	filePath = rhsFilePath;
	nRows = rhsNRows;
	nColumns = rhsNColumns;
	layer = rhsLayer;

	GetImageSizes();
}

Image::~Image()
{
	myRenderManager = nullptr;
	timePipe = nullptr;
}

void Image::PlayAnimation(Animation rhsAnimationToPlay)
{
	animationToPlay = rhsAnimationToPlay;
	playingAnimation = true;

	if (animationToPlay.newFilePath != "" && animationToPlay.newFilePath != filePath)
	{
		filePath = animationToPlay.newFilePath;
		nColumns = animationToPlay.nColumns;
		nRows = animationToPlay.nRows;
	}

	if (animationToPlay.startFrame % nColumns == 0)
	{
		framePositionColumn = nColumns;
		framePositionRow = animationToPlay.startFrame / nColumns - 1;
	}
	else
	{
		std::floor(framePositionColumn = animationToPlay.startFrame % nColumns);
		(framePositionRow = animationToPlay.startFrame / nColumns);
	}
}

Animation Image::GetCurrentAnimation()
{
	return animationToPlay;
}

bool Image::EndOfAnimation()
{
	return endOfAnimation;
}

void Image::StopAnimation()
{
	playingAnimation = false;
	frameTime = 0.0f;
	currentFrame = 0;
	endOfAnimation = true;
}

void Image::GetImageSizes()
{
	myRenderManager->GetImageSize(this);
}

void Image::Start()
{
	timePipe = timePipe->GetTimePipelineInstance();
}

void Image::Update()
{
	if (endOfAnimation)
	{
		endOfAnimation = false;
	}
	if (playingAnimation)
	{
		frameTime += timePipe->GetDeltaTIme();

		if (frameTime >= 1/animationToPlay.velocity / 10)
		{			

			if ((animationToPlay.startFrame + currentFrame) % nColumns == 0)
			{
				framePositionColumn = nColumns;
				framePositionRow = (animationToPlay.startFrame + currentFrame) / nColumns - 1;
			}
			else
			{
				std::floor(framePositionColumn = (animationToPlay.startFrame + currentFrame) % nColumns);
				(framePositionRow = (animationToPlay.startFrame + currentFrame) / nColumns);

				//std::cout << std::floor(framePositionRow = (animationToPlay.startFrame + currentFrame) / nColumns) << std::endl;
			}
			if (animationToPlay.startFrame < animationToPlay.endFrame)
			{
				++currentFrame;

				if (animationToPlay.startFrame + currentFrame > animationToPlay.endFrame + 1)
				{
					if (animationToPlay.loop)
					{
						currentFrame = 0;
					}
					else
					{
						StopAnimation();
					}
				}
			}
			else
			{
				--currentFrame;

				if (animationToPlay.startFrame + currentFrame < animationToPlay.endFrame + 1)
				{
					if (animationToPlay.loop)
					{
						currentFrame = 0;
					}
					else
					{
						StopAnimation();
					}
				}
			}

			frameTime = 0;
		}
	}
}

