#include "Sound.h"

void Sound::PlaySound(std::string file)
{
	soundPlay = true;
	filePath = file;
}
