#include "../SimpleFMOD/SimpleFMOD.h"
#include <functional>
#include <memory>
#include <iostream>

using namespace SFMOD;

// Some example sound generators
// These receive a value from 0.0-1.0 indicating the position in the repeating samples to generate
// and return a value from -1.0 to +1.0 indicating the volume at the current sample position
typedef std::function<double (double)> GeneratorType;

class Generators
{
public:
	// Sine wave
	static double Sine(double samplePos)
	{
		return sin(samplePos * M_PI*2);
	}

	// Sawtooth
	static double Sawtooth(double samplePos)
	{
		if (samplePos == 0)
			return 0.f;

		return (2.f / samplePos) - 1.f;
	}

	// Square wave
	static double Square(double samplePos)
	{
		return (samplePos < 0.5f? 1.f : -1.f);
	}

	// White noise ("static")
	static double WhiteNoise(double samplePos)
	{
		return static_cast<double>(rand()) / RAND_MAX;
	}
};

// Class which generates audio according to the specified function, frequency, sample rate and volume
class Generator
{
private:
	// The sound
	Song sound;

	// Sample rate
	int const sampleRate;

	// Number of channels
	int const channels;

	// Length of sample in seconds before it repeats
	int const lengthInSeconds;

	// Frequency to generate
	int const frequency;

	// Volume (0.0-1.0)
	float const volume;

	// The function to use to generate samples
	GeneratorType generator;

	// How many samples we have generated so far
	int samplesElapsed;

public:
	// Constructor
	Generator(SimpleFMOD &fmod, GeneratorType generator, int frequency, int sampleRate, int channels, int lengthInSeconds, float volume)
		: generator(generator), frequency(frequency), sampleRate(sampleRate), channels(channels),
		  lengthInSeconds(lengthInSeconds), volume(volume), samplesElapsed(0)
	{
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

		// Pointer to the object we are using to generate the samples
		// (our callbacks query this data to access a concrete instance of the class from our static member callback functions)
		soundInfo.userdata = this;

		// Create a user-defined sound with FMOD_OPENUSER
		sound = fmod.LoadSong(nullptr, nullptr, FMOD_OPENUSER, soundInfo);
	}

	// Start playing
	FMOD::Channel *Start()
	{
		return sound.Start();
	}

	// Get reference to sound
	Song &Get()
	{
		return sound;
	}

	// Change the sound being generated
	void SetGenerator(GeneratorType g)
	{
		generator = g;
	}

	// FMOD Callbacks
	static FMOD_RESULT F_CALLBACK PCMRead(FMOD_SOUND *sound, void *data, unsigned int length);
	static FMOD_RESULT F_CALLBACK PCMSetPosition(FMOD_SOUND *sound, int subsound, unsigned int position, FMOD_TIMEUNIT postype);
};

// Generate new samples
// We must fill "length" bytes in the buffer provided by "data"
FMOD_RESULT Generator::PCMRead(FMOD_SOUND *sound, void *data, unsigned int length)
{
	// Get the object we are using
	// Note that FMOD_Sound * must be cast to FMOD::Sound * to access it
	Generator *me;
	((FMOD::Sound *) sound)->getUserData((void **) &me);

	// Get buffer in 16-bit format
    signed short *stereo16BitBuffer = (signed short *)data;

	// A 2-channel 16-bit stereo stream uses 4 bytes per sample
    for (unsigned int sample = 0; sample < length / 4; sample++)
    {
		// Get the position in the sample
		double pos = me->frequency * static_cast<float>(me->samplesElapsed) / me->sampleRate;

		// Modulo it to a value between 0 and 1
		pos = pos - floor(pos);

		// The generator function returns a value from -1 to 1 so we multiply this by the
		// maximum possible volume of a 16-bit PCM sample (32767) to get the true volume to store

		// Generate a sample for the left channel
		*stereo16BitBuffer++ = (signed short)(me->generator(pos) * 32767.0f * me->volume);

		// Generate a sample for the right channel
		if (me->channels == 2)
			*stereo16BitBuffer++ = (signed short)(me->generator(pos) * 32767.0f * me->volume);

		// Increment number of samples generated
		me->samplesElapsed++;
    }

    return FMOD_OK;
}

FMOD_RESULT Generator::PCMSetPosition(FMOD_SOUND *sound, int subsound, unsigned int position, FMOD_TIMEUNIT postype)
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
	int soundLengthSeconds = 5;

	// Types of sound generator
	GeneratorType generators[] = {
		Generators::Sine,
		Generators::Sawtooth,
		Generators::Square,
		Generators::WhiteNoise
	};

	// Which generator to use
	int generatorId = 0;
	int numGenerators = 4;

	// Frequency to generate (Hz)
	int frequency = 800;

	// Volume level (0.0 - 1.0)
	float volume = 0.3f;

	// Set up FMOD
	SimpleFMOD fmod;

	// Set up sound generator
	Generator generator(fmod, generators[generatorId], frequency, sampleRate, channels, soundLengthSeconds, volume);

	// Start playback and get the channel and a reference to the sound
	FMOD::Channel *channel = generator.Start();
	Song *sound = &generator.Get();

	// Print instructions
	std::cout <<
		"FMOD Sound Generator Demo - (c) Katy Coe 2013 - www.djkaty.com" << std::endl <<
		"==============================================================" << std::endl << std::endl <<
		"Press:" << std::endl << std::endl <<
		"  G - Change sound generator" << std::endl <<
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

			paused = sound->GetPaused();
            channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
            sound->Get()->getLength(&lenms, FMOD_TIMEUNIT_MS);

            printf("Time %02d:%02d:%02d/%02d:%02d:%02d : %s\r", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused? "Paused " : "Playing");
        }

		// G - Change generator
		if (GetAsyncKeyState('G'))
		{
			sound->Stop();
			generatorId = (generatorId + 1) % numGenerators;
			generator.SetGenerator(generators[generatorId]);
			sound->Start();

			while (GetAsyncKeyState('G'))
				;
		}

		// P - Toggle pause
		if (GetAsyncKeyState('P'))
		{
			sound->TogglePause();

			while (GetAsyncKeyState('P'))
				;
		}

		// Q - Quit
		if (GetAsyncKeyState('Q'))
			quit = true;
	}
}