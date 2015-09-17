#include "../SimpleFMOD/SimpleFMOD.h"
#include <functional>
#include <memory>
#include <iostream>

using namespace SFMOD;

// Generate new samples
// We must fill "length" bytes in the buffer provided by "data"
FMOD_RESULT F_CALLBACK PCMRead(FMOD_SOUND *sound, void *data, unsigned int length)
{
	// Sample rate
	static int const sampleRate = 44100;

	// Frequency to generate (Hz)
	static int const frequency = 800;

	// Volume level (0.0 - 1.0)
	static float const volume = 0.3f;

	// How many samples we have generated so far
	static int samplesElapsed = 0;

	// Get buffer in 16-bit format
    signed short *stereo16BitBuffer = (signed short *)data;

	// A 2-channel 16-bit stereo stream uses 4 bytes per sample
    for (unsigned int sample = 0; sample < length / 4; sample++)
    {
		// Get the position in the sample
		double pos = frequency * static_cast<float>(samplesElapsed) / sampleRate;

		// The generator function returns a value from -1 to 1 so we multiply this by the
		// maximum possible volume of a 16-bit PCM sample (32767) to get the true volume to store

		// Generate a sample for the left channel
		*stereo16BitBuffer++ = (signed short)(sin(pos * M_PI*2) * 32767.0f * volume);

		// Generate a sample for the right channel
		*stereo16BitBuffer++ = (signed short)(sin(pos * M_PI*2) * 32767.0f * volume);

		// Increment number of samples generated
		samplesElapsed++;
    }

    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK PCMSetPosition(FMOD_SOUND *sound, int subsound, unsigned int position, FMOD_TIMEUNIT postype)
{
	// If you need to process the user changing the playback position (seeking), do it here

	return FMOD_OK;
}

// Program entry point
int main()
{
	// The sample rate, number of channels and total time in seconds before the gnerated sample repeats
	int sampleRate = 44100;
	int channels = 2;
	int lengthInSeconds = 5;

	// Set up FMOD
	SimpleFMOD fmod;

	// Set up the sound
	FMOD_CREATESOUNDEXINFO soundInfo;

	memset(&soundInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
	soundInfo.cbsize            = sizeof(FMOD_CREATESOUNDEXINFO);

	// The number of samples to fill per call to the PCM read callback (here we go for 1 second's worth)
	soundInfo.decodebuffersize  = sampleRate;

	// The length of the entire sample in bytes, calculated as:
	// Sample rate * number of channels * bits per sample per channel * number of seconds
	soundInfo.length            = sampleRate * channels * sizeof(signed short) * lengthInSeconds;

	// Number of channels and sample rate
	soundInfo.numchannels       = channels;
	soundInfo.defaultfrequency  = sampleRate;

	// The sound format (here we use 16-bit signed PCM)
	soundInfo.format            = FMOD_SOUND_FORMAT_PCM16;

	// Callback for generating new samples
	soundInfo.pcmreadcallback   = PCMRead;

	// Callback for when the user seeks in the playback
	soundInfo.pcmsetposcallback = PCMSetPosition;

	// Create a user-defined sound with FMOD_OPENUSER
	Song sound = fmod.LoadSong(nullptr, nullptr, FMOD_OPENUSER, soundInfo);

	// Start playback and get the channel and a reference to the sound
	FMOD::Channel *channel = sound.Start();

	// Print instructions
	std::cout <<
		"FMOD Sound Generator Demo - (c) Katy Coe 2013 - www.djkaty.com" << std::endl <<
		"==============================================================" << std::endl << std::endl <<
		"Press:" << std::endl << std::endl <<
		"  P - Toggle pause" << std::endl <<
		"  Q - Quit" << std::endl << std::endl;

	bool quit = false;

	while (!quit)
	{
		// Update FMOD
		fmod.Update();

		// Print statistics
        if (channel)
        {
            unsigned int ms;
            unsigned int lenms;
            bool         paused;

			paused = sound.GetPaused();
            channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
            sound.Get()->getLength(&lenms, FMOD_TIMEUNIT_MS);

            printf("Time %02d:%02d:%02d/%02d:%02d:%02d : %s\r", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused? "Paused " : "Playing");
        }

		// P - Toggle pause
		if (GetAsyncKeyState('P'))
		{
			sound.TogglePause();

			while (GetAsyncKeyState('P'))
				;
		}

		// Q - Quit
		if (GetAsyncKeyState('Q'))
			quit = true;
	}
}