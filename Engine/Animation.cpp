#include "Animation.h"
Animation::Animation( int rhsStartFrame, int rhsEndFrame, float rhsVelocity, bool rhsLoop)
{
	startFrame = rhsStartFrame;
	endFrame = rhsEndFrame - 1;
	velocity = rhsVelocity;
	loop = rhsLoop;
};

Animation::Animation(std::string newImage, int newNColumns, int newNRows, int rhsStartFrame, int rhsEndFrame, float rhsVelocity, bool rhsLoop)
{
    newFilePath = newImage;
    nColumns = newNColumns;
    nRows = newNRows;
    startFrame = rhsStartFrame;
    endFrame = rhsEndFrame - 1;
    velocity = rhsVelocity;
    loop = rhsLoop;
}

bool Animation::operator==(const Animation& other) const
{
    if (
       startFrame != other.startFrame
    || endFrame != other.endFrame
    || velocity != other.velocity
    || loop != other.loop
    )
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Animation::operator!=(const Animation& other) const
{
    return !(*this == other);
}