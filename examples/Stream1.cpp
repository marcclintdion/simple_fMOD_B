#include "fmod.hpp"
#include "fmod_errors.h"
#include <iostream>
#include <Windows.h>

#define _USE_MATH_DEFINES

#include <math.h>

void FMODErrorCheck(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}

int main()
{
	// ================================================================================================
	// Application-independent initialization
	// ================================================================================================

	FMOD::System *system;
	FMOD_RESULT result;
	unsigned int version;
	int numDrivers;
	FMOD_SPEAKERMODE speakerMode;
	FMOD_CAPS caps;
	char name[256];

	// Create FMOD interface object
	result = FMOD::System_Create(&system);
	FMODErrorCheck(result);

	// Check version
	result = system->getVersion(&version);
	FMODErrorCheck(result);

	if (version < FMOD_VERSION)
	{
		std::cout << "Error! You are using an old version of FMOD " << version << ". This program requires " << FMOD_VERSION << std::endl;
		return 0;
	}
	
	// Get number of sound cards
	result = system->getNumDrivers(&numDrivers);
	FMODErrorCheck(result);
	
	// No sound cards (disable sound)
	if (numDrivers == 0)
	{
		result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		FMODErrorCheck(result);
	}

	// At least one sound card
	else
	{
		// Get the capabilities of the default (0) sound card
		result = system->getDriverCaps(0, &caps, 0, &speakerMode);
		FMODErrorCheck(result);
	
		// Set the speaker mode to match that in Control Panel
		result = system->setSpeakerMode(speakerMode);
		FMODErrorCheck(result);
	
		// Increase buffer size if user has Acceleration slider set to off
		if (caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			result = system->setDSPBufferSize(1024, 10);
			FMODErrorCheck(result);
		}
	
		// Get name of driver
		result = system->getDriverInfo(0, name, 256, 0);
		FMODErrorCheck(result);
	
		// SigmaTel sound devices crackle for some reason if the format is PCM 16-bit.
		// PCM floating point output seems to solve it.
		if (strstr(name, "SigmaTel"))
		{
			result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
			FMODErrorCheck(result);
		}
	}

	// Initialise FMOD
	result = system->init(100, FMOD_INIT_NORMAL, 0);

	// If the selected speaker mode isn't supported by this sound card, switch it back to stereo
	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		FMODErrorCheck(result);
	
		result = system->init(100, FMOD_INIT_NORMAL, 0);
	}
	FMODErrorCheck(result);

	// ================================================================================================
	// Application-specific code
	// ================================================================================================

	bool quit = false;
	bool fading = false;
	int fadeLength = 3000;
	int fadeStartTick;

	// Open music as a stream
	FMOD::Sound *song1, *song2, *effect;
	result = system->createStream("Song1.mp3", FMOD_DEFAULT, 0, &song1);
	FMODErrorCheck(result);
	result = system->createStream("Song2.mp3", FMOD_DEFAULT, 0, &song2);
	FMODErrorCheck(result);

	// Load sound effects into memory (not streaming)
	result = system->createSound("Effect.mp3", FMOD_DEFAULT, 0, &effect);
	FMODErrorCheck(result);

	// Assign each song to a channel and start them paused
	FMOD::Channel *channel1, *channel2;
	result = system->playSound(FMOD_CHANNEL_FREE, song1, true, &channel1);
	FMODErrorCheck(result);
	result = system->playSound(FMOD_CHANNEL_FREE, song2, true, &channel2);
	FMODErrorCheck(result);

	// Songs should repeat forever
	channel1->setLoopCount(-1);
	channel2->setLoopCount(-1);

	// Print instructions
	std::cout <<
		"FMOD Simple Demo - (c) Katy Coe 2012 - www.djkaty.com" << std::endl <<
		"=====================================================" << std::endl << std::endl <<
		"Press:" << std::endl << std::endl <<
		"  1 - Toggle song 1 pause on/off" << std::endl <<
		"  2 - Toggle song 2 pause on/off" << std::endl <<
		"  F - Fade from song 1 to song 2" << std::endl <<
		"  S - Play one-shot sound effect" << std::endl <<
		"  Q - Quit" << std::endl;

	while (!quit)
	{
		// Per-frame FMOD update
		FMODErrorCheck(system->update());

		// Q - Quit
		if (GetAsyncKeyState('Q'))
			quit = true;

		// 1 - Toggle song 1 pause state
		if (GetAsyncKeyState('1'))
		{
			bool isPaused;
			channel1->getPaused(&isPaused);
			channel1->setPaused(!isPaused);
			while (GetAsyncKeyState('1'));
		}

		// 2 - Toggle song 2 pause state
		if (GetAsyncKeyState('2'))
		{
			bool isPaused;
			channel2->getPaused(&isPaused);
			channel2->setPaused(!isPaused);
			while (GetAsyncKeyState('2'));
		}

		// F - Begin fade from song 1 to song 2
		if (GetAsyncKeyState('F'))
		{
			channel1->setVolume(1.0f);
			channel2->setVolume(0.0f);
			channel1->setPaused(false);
			channel2->setPaused(false);
			fading = true;
			fadeStartTick = GetTickCount();

			while (GetAsyncKeyState('F'));
		}

		// Play one-shot sound effect (without storing channel handle)
		if (GetAsyncKeyState('S'))
		{
			system->playSound(FMOD_CHANNEL_FREE, effect, false, 0);

			while (GetAsyncKeyState('S'));
		}

		// Fade function if fade is in progress
		if (fading)
		{
			// Get volume from 0.0f - 1.0f depending on number of milliseconds elapsed since fade started
			float volume = min(static_cast<float>(GetTickCount() - fadeStartTick) / fadeLength, 1.0f);

			// Fade is over if song 2 has reached full volume
			if (volume == 1.0f)
			{
				fading = false;
				channel1->setPaused(true);
				channel1->setVolume(1.0f);
			}

			// Translate linear volume into a smooth sine-squared fade effect
			volume = static_cast<float>(sin(volume * M_PI / 2));
			volume *= volume;

			// Fade song 1 out and song 2 in
			channel1->setVolume(1.0f - volume);
			channel2->setVolume(volume);
		}
	}

	// Free resources
	FMODErrorCheck(song1->release());
	FMODErrorCheck(song2->release());
	FMODErrorCheck(effect->release());
	FMODErrorCheck(system->release());
}