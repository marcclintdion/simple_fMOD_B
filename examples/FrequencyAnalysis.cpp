// FMOD Frequency Analysis demo
// Written by Katy Coe (c) 2013
// No unauthorized copying or distribution
// www.djkaty.com

#include "../SimpleFMOD/SimpleFMOD.h"
#include "Simple2D.h"

#include <queue>

using namespace SFMOD;
using namespace S2D;

class FrequencyAnalysis : public Simple2D
{
private:
	// FMOD
	SimpleFMOD fmod;
	Song song;

	// Graphics
	TextFormat freqTextFormat;
	Gradient freqGradient;

	// Normalization toggle and sample size
	bool enableNormalize;
	int sampleSize;

	// Beat detection parameters
	float beatThresholdVolume;
	int beatThresholdBar;
	unsigned int beatSustain;
	unsigned int beatPostIgnore;

	int beatLastTick;
	int beatIgnoreLastTick;

	// List of how many ms ago the last beats were
	std::queue<int> beatTimes;
	unsigned int beatTrackCutoff;

	// When the music was last unpaused
	int musicStartTick;

public:
	FrequencyAnalysis();
	void DrawScene();

	virtual bool OnKeyCharacter(int, int, bool, bool);
};

// Initialize application
FrequencyAnalysis::FrequencyAnalysis()
{
	// Make paintbrushes
	freqTextFormat = MakeTextFormat(L"Verdana", 10.0f);
	freqGradient = MakeBrush(Colour::Green, Colour::Red);

	song = fmod.LoadSong("Song.mp3", FMOD_SOFTWARE);
	song.Start(true);

	// Load song
	enableNormalize = true;
	sampleSize = 64;

	// Set beat detection parameters
	beatThresholdVolume = 0.3f;
	beatThresholdBar = 0;
	beatSustain = 150;
	beatPostIgnore = 250;
	beatTrackCutoff = 10000;

	beatLastTick = 0;
	beatIgnoreLastTick = 0;

	musicStartTick = 0;
}

// Handle keypresses
bool FrequencyAnalysis::OnKeyCharacter(int key, int rc, bool prev, bool trans)
{
	// Toggle pause
	if (key == 'P' || key == 'p')
	{
		song.TogglePause();

		// Reset bpm estimation if needed
		if (musicStartTick == 0 && !enableNormalize && !song.GetPaused())
		{
			musicStartTick = GetTickCount();
			beatTimes.empty();
		}

		else if (song.GetPaused())
			musicStartTick = 0;
	}

	// Toggle normalization
	if (key == 'N' || key == 'n')
	{
		enableNormalize = !enableNormalize;

		// Reset bpm estimation if needed
		if (!enableNormalize && !song.GetPaused())
		{
			musicStartTick = GetTickCount();
			beatTimes.empty();
		}
	}

	// Decrease FFT sample size
	if (key == '1')
		sampleSize = max(sampleSize / 2, 64);

	// Increase FFT sample size
	if (key == '2')
		sampleSize = min(sampleSize * 2, 8192);

	return true;
}

// Per-frame code
void FrequencyAnalysis::DrawScene()
{
	// Update FMOD
	fmod.Update();

	// Frequency analysis
	float *specLeft, *specRight, *spec;
	spec = new float[sampleSize];
	specLeft = new float[sampleSize];
	specRight = new float[sampleSize];

	// Get average spectrum for left and right stereo channels
	song.GetChannel()->getSpectrum(specLeft, sampleSize, 0, FMOD_DSP_FFT_WINDOW_RECT);
	song.GetChannel()->getSpectrum(specRight, sampleSize, 1, FMOD_DSP_FFT_WINDOW_RECT);

	for (int i = 0; i < sampleSize; i++)
		spec[i] = (specLeft[i] + specRight[i]) / 2;

	// Find max volume
	auto maxIterator = std::max_element(&spec[0], &spec[sampleSize]);
	float maxVol = *maxIterator;

	// Normalize
	// Note: &spec[0] changed to a Microsoft checked iterator here to avoid warnings in Visual Studio 2012 (works either way)
	if (enableNormalize && maxVol != 0)
		std::transform(&spec[0], &spec[sampleSize], stdext::checked_array_iterator<float *>(spec, sampleSize), [maxVol] (float dB) -> float { return dB / maxVol; });

	// Find frequency range of each array item
	float hzRange = (44100 / 2) / static_cast<float>(sampleSize);

	// Detect beat if normalization disabled
	if (!enableNormalize)
	{
		if (spec[beatThresholdBar] >= beatThresholdVolume && beatLastTick == 0 && beatIgnoreLastTick == 0)
		{
			beatLastTick = GetTickCount();
			beatTimes.push(beatLastTick);

			while(GetTickCount() - beatTimes.front() > beatTrackCutoff)
			{
				beatTimes.pop();
				if (beatTimes.size() == 0)
					break;
			}
		}

		if (GetTickCount() - beatLastTick < beatSustain)
			Text(100, 220, "BEAT", Colour::White, MakeTextFormat(L"Verdana", 48.0f));

		else if (beatIgnoreLastTick == 0 && beatLastTick != 0)
		{
			beatLastTick = 0;
			beatIgnoreLastTick = GetTickCount();
		}

		if (GetTickCount() - beatIgnoreLastTick >= beatPostIgnore)
			beatIgnoreLastTick = 0;
	}

	// Predict BPM
	float msPerBeat, bpmEstimate;
	
	if (beatTimes.size() >= 2)
	{
		msPerBeat = (beatTimes.back() - beatTimes.front()) / static_cast<float>(beatTimes.size() - 1);
		bpmEstimate = 60000 / msPerBeat;
	}
	else
		bpmEstimate = 0;

	// Draw display
	Text(10, 10, "Press P to toggle pause, N to toggle normalize, 1 and 2 to adjust FFT size", Colour::White, MakeTextFormat(L"Verdana", 14.0f));

	Text(10, 30, "Sample size: " + StringFactory(sampleSize) + "  -  Range per sample: " + StringFactory(hzRange) + "Hz  -  Max vol this frame: " + StringFactory(maxVol), Colour::White, MakeTextFormat(L"Verdana", 14.0f));

	// BPM estimation
	if (!enableNormalize)
	{
		if (GetTickCount() - musicStartTick >= beatTrackCutoff && musicStartTick != 0)
			Text(10, ResolutionY - 20, "Estimated BPM: " + StringFactory(bpmEstimate) + " (last " + StringFactory(beatTrackCutoff / 1000) + " seconds)", Colour::White, MakeTextFormat(L"Verdana", 14.0f));
		else if (musicStartTick != 0)
			Text(10, ResolutionY - 20, "Estimated BPM: calculating for next " + StringFactory(beatTrackCutoff - (GetTickCount() - musicStartTick)) + " ms", Colour::White, MakeTextFormat(L"Verdana", 14.0f));
		else
			Text(10, ResolutionY - 20, "Paused", Colour::White, MakeTextFormat(L"Verdana", 14.0f));
	}
	else
		Text(10, ResolutionY - 20, "Disable normalization to enable BPM calculation", Colour::White, MakeTextFormat(L"Verdana", 14.0f));

	// Numerical FFT display
	int nPerRow = 16;

	for (int y = 0; y < sampleSize / nPerRow; y++)
		for (int x = 0; x < nPerRow; x++)
			Text(x * 40 + 10, y * 20 + 60, StringFactory(floor(spec[y * nPerRow + x] * 1000)), Colour::White, freqTextFormat);

	// VU bars
	int blockGap = 4 / (sampleSize / 64);
	int blockWidth = static_cast<int>((static_cast<float>(ResolutionX) * 0.8f) / static_cast<float>(sampleSize) - blockGap);
	int blockMaxHeight = 200;

	for (int b = 0; b < sampleSize - 1; b++)
		FillRectangleWH(static_cast<int>(ResolutionX * 0.1f + (blockWidth + blockGap) * b),
						ResolutionY - 50,
						blockWidth,
						static_cast<int>(-blockMaxHeight * spec[b]),
						freqGradient);

	// Clean up
	delete [] spec;
	delete [] specLeft;
	delete [] specRight;
}

void Simple2DStart()
{
	FrequencyAnalysis test;
	test.SetWindowName(L"FMOD Frequency Analysis");
	test.SetBackgroundColour(Colour::Black);
	test.SetResizableWindow(false);
	test.Run();
}
