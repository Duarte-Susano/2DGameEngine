#include "SoundManager.h"
#include <al.h>
#include <alc.h>
#include <AudioFile.h>



#define OpenAL_ErrorCheck(message)\
{\
	ALenum error = alGetError();\
	if(error != AL_NO_ERROR)\
	{\
		std::cerr << "OpenAL Error: " << error << "with call for" << #message << std::endl;\
	}\
}


#define alec(FUNCTION_CALL)\
FUNCTION_CALL;\
OpenAL_ErrorCheck(FUNCTION_CALL)



SoundManager::SoundManager()
{
	//Find Default Audio Device
	const ALCchar* defaultDeviceString = alcGetString(/*device*/nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
	device = alcOpenDevice(defaultDeviceString);

	if (!device)
	{
		std::cerr << "failed to get the default device for OpenAL" << std::endl;
	}

	std::cout << "OpenAl Device:" << alcGetString(device, ALC_DEVICE_SPECIFIER) << std::endl;



	// Create an OpenAL Audio context from the device
	context = alcCreateContext(device, /*attrlist*/ nullptr);



	//Activate this context so that OpenAl state modifications are applied to the context
	if (!alcMakeContextCurrent(context))
	{
		std::cerr << "failed to make OpenAL context the current context" << std::endl;

	}
	OpenAL_ErrorCheck("Make context current");

	OpenAL_ErrorCheck(device);
	OpenAL_ErrorCheck(context);

	//Create a listener (ie the player)

	alec(alListener3f(AL_POSITION, 0.f, 0.f, 0.f));
	alec(alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f));
	ALfloat forwardAndUpVectors[] = {

		/*forward*/ 1.f, 0.f, 0.f,
		/*up*/ 0.f,1.f,0.f
	};
}

SoundManager::~SoundManager()
{
	for (std::pair<std::string, ALuint> source: sources)
	{
		alDeleteSources(1, &source.second);
	}	

	for (int i = 0; i < buffers.size(); ++i)
	{
		alec(alDeleteBuffers(1, &buffers[i]));
	}

	alec(alcDestroyContext(context));
	alec(alcCloseDevice(device));
	alec(alcMakeContextCurrent(nullptr));
}

void SoundManager::SpawnSounds(std::vector<Object*> objects)
{
	std::vector<Sound> sounds;
	
	for (Object* obj: objects)
	{
		std::vector<Sound*> objSounds;
		objSounds = obj->GetComponents<Sound>();

		for (Sound* sound : objSounds)
		{
			if (sound->soundPlay)
			{
				sounds.push_back(*sound);
				sound->soundPlay = false;
			}
		}
	}
	
	//Create buffers that hold our sound data
	for (Sound sound: sounds)
	{
		if (!hasSoundFile[sound.filePath])
		{

			if (!soundFiles[sound.filePath].load(sound.filePath))
			{
				std::cerr << "failed to load the test mono sound file" << std::endl;
			}

			std::vector<uint8_t> monoPCMDataBytes;
			soundFiles[sound.filePath].writePCMToBuffer(monoPCMDataBytes);
			auto convertFileToOpenALFromat = [](const AudioFile<float>& audioFile)
			{
				int bitDepth = audioFile.getBitDepth();
				if (bitDepth == 16)
					return audioFile.isStereo() ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
				else if (bitDepth == 8)
					return audioFile.isStereo() ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
				else
					std::cout << "this shouldnt happen";
			};

			hasSoundFile[sound.filePath] = true;

			ALuint buffer;
			buffers.push_back(buffer);
			alec(alGenBuffers(1, &buffer));

			alec(alBufferData(buffer, convertFileToOpenALFromat(soundFiles[sound.filePath]), monoPCMDataBytes.data(), monoPCMDataBytes.size(), soundFiles[sound.filePath].getSampleRate()));


			//Create a sound source that plays our mono sound (from the sound buffer)
			alec(alGenSources(1, &sources[sound.filePath]));
			alec(alSource3f(sources[sound.filePath], AL_POSITION, 1.f, 0.f, 0.f));
			alec(alSource3f(sources[sound.filePath], AL_VELOCITY, 0.f, 0.f, 0.f));
			alec(alSourcef(sources[sound.filePath], AL_PITCH, 1.0f));
			alec(alSourcef(sources[sound.filePath], AL_GAIN, 1.0f));
			alec(alSourcei(sources[sound.filePath], AL_LOOPING, AL_FALSE));
			alec(alSourcei(sources[sound.filePath], AL_BUFFER, buffer));
		}

		alec(alSourcePlay(sources[sound.filePath]));

	}
}
