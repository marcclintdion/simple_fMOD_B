#include "../SimpleFMOD/SimpleFMOD.h"

using namespace SFMOD;

int main()
{
	SimpleFMOD fmod;

	// ================================================================================================
	// Application-specific code
	// ================================================================================================

	bool quit = false;

	// Open audio
	Song song1 = fmod.LoadSong("Song1.mp3");
	Song song2 = fmod.LoadSong("Song2.mp3");
	SoundEffect effect = fmod.LoadSoundEffect("Effect.mp3");

	song1.Start(true);
	song2.Start(true);

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
		fmod.Update();

		// Q - Quit
		if (GetAsyncKeyState('Q'))
			quit = true;

		// 1 - Toggle song 1 pause state
		if (GetAsyncKeyState('1'))
		{
			song1.TogglePause();
			while (GetAsyncKeyState('1'));
		}

		// 2 - Toggle song 2 pause state
		if (GetAsyncKeyState('2'))
		{
			song2.TogglePause();
			while (GetAsyncKeyState('2'));
		}

		// F - Begin fade from song 1 to song 2
		if (GetAsyncKeyState('F'))
		{
			song1.SetVolume(1.0f);
			song2.SetVolume(0.0f);
			song1.SetPaused(false);
			song2.SetPaused(false);

			song1.Fade(3000);
			song2.Fade(3000, 1.0f);

			while (GetAsyncKeyState('F'));
		}

		// Play one-shot sound effect (without storing channel handle)
		if (GetAsyncKeyState('S'))
		{
			effect.Play();
			while (GetAsyncKeyState('S'));
		}
	}
}