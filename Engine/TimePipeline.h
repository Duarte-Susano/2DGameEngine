#pragma once


class TimePipeline
{
public:
	//Get instance
	TimePipeline* GetTimePipelineInstance();
	//Updates variables
	void UpdateTime();
	//Get time from the moment the game starts
	int GetCurrentTime();
	//Returns the Delta Time
	float GetDeltaTIme();
private:
	//my instance
	static TimePipeline* instance;
	//time variables
	int prevTime = 0;
	int currentTime = 0;
	float deltaTime = 0.0f;
};