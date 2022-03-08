#include "TimePipeline.h"
#include "SDL.h"

TimePipeline* TimePipeline::GetTimePipelineInstance()
{
    if (!instance)
        instance = new TimePipeline();
    return instance;
}

void TimePipeline::UpdateTime()
{
    prevTime = currentTime;
    currentTime = SDL_GetTicks();
    deltaTime = (currentTime - prevTime) / 1000.0f;
}

int TimePipeline::GetCurrentTime()
{
    return SDL_GetTicks();
}

float TimePipeline::GetDeltaTIme()
{
    return deltaTime;
}
