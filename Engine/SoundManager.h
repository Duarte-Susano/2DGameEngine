#pragma once
#include <iostream>
#include <al.h>
#include <alc.h>
#include <AudioFile.h>
#include <unordered_map>
#include <vector>
#include "Object.h"
#include "Sound.h"

class SoundManager
{
public:

	SoundManager();
	~SoundManager();
	void SpawnSounds(std::vector<Object*> objects);

private:

	std::vector <ALuint> buffers;

	AudioFile<float> monoSoundFile;
	ALCdevice* device = nullptr;
	ALCcontext* context = nullptr;
	std::unordered_map<std::string, AudioFile<float>> soundFiles;
	std::unordered_map<std::string, bool> hasSoundFile;
	std::unordered_map<std::string, ALuint> sources;

};

