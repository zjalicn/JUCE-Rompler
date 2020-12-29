/*
  ==============================================================================

    FilterDisplay.cpp
    Created: 28 Dec 2020 12:05:56am
    Author:  nzjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterDisplay.h"

//==============================================================================
FilterDisplay::FilterDisplay(juce::AudioProcessorValueTreeState& vt) : mAVPTS(vt), mFFT(fftOrder)
{
	// Timer to update filter magnitude response graph
	startTimer(10);
}

FilterDisplay::~FilterDisplay()
{
	// Empty destructor
}

//==============================================================================

void FilterDisplay::paint(juce::Graphics& g)
{
	// Rounded rectangle around the graph with same but darker colour as the background
	g.setColour(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId).darker(.8f));
	g.fillRoundedRectangle(0.f, 0.f, static_cast<float>(getWidth()), static_cast<float>(getHeight()), 10.f);   // draw an outline around the component

	// Graph frequency response====================================

	// Needed variables
	// Length of usable values in fft (fs / 2)
	float fftLen = fftSize / 2.f;
	// Sampling frequency
	auto sampleRate = mAVPTS.getRawParameterValue("SAMPLE_RATE")->load();
	// Start point in x-axis (20 Hz to bins and then to log scale)
	float minX = log10(20.f * (static_cast<float>(fftSize) / sampleRate));
	// Scale x-axis so that start is at 20 Hz and end at 20 000 Hz
	float scaleX = getWidth() / (log10(20000.f * (static_cast<float>(fftSize) / sampleRate)) - minX);
	// Scale y-axis from -12 dB to 12 dB
	float maxY = 12.f;
	float scaleY = (getHeight() / 2.f) / maxY;
	float endX = 0.f;
	float endY = 0.f;
	bool startFound = false;

	// Paint markers if the graph is large enough
	//if (getHeight() > 100.f)
	paintMarkers(g, scaleX, minX, sampleRate);

	// Path of the frequency response
	juce::Path myPath;
	// Path colour
	g.setColour(juce::Colours::white);

	for (auto i = 0; i < fftLen; ++i)
	{
		// X scaled for window size and log10 scale
		endX = i == 0 ? 0.f : static_cast<float>((log10(i) - minX) * scaleX);
		endY = getHeight() / 2.f - juce::Decibels::gainToDecibels(mFilteredImpulse[i]) * scaleY;

		// Start of the path
		if (startFound == false && (endY > 0.f && endY < getHeight() + 20.f))
		{
			myPath.startNewSubPath(endX, endY);
			startFound = true;
		}
		else
		{
			// Rest of the path that is inside the figure area
			if (endY > 0 && endY < getHeight() + 20.f && startFound == true)
				myPath.lineTo(endX, endY);
		}
	}
	// Draw path with curves
	juce::Path roundedPath = myPath.createPathWithRoundedCorners(5.0f);
	g.strokePath(roundedPath, juce::PathStrokeType(2.f));
}

//==============================================================================

void FilterDisplay::paintMarkers(juce::Graphics& g, float scaleX, float minX, float fs)
{
	// Dash size for dashed lines
	float myDash[2] = { 2.f, 2.f };
	// Colour for lines (horizontal and vertical)
	g.setColour(juce::Colours::white.darker(.8f));

	for (auto i = 1; i < 8; ++i)
	{
		float width = static_cast<float> (getWidth());
		float height = static_cast<float> (getHeight());
		juce::Line<float> horizontalLine(0.f, height * (i / 8.f), width, height * (i / 8.f));
		if (i == 4)
			g.drawLine(horizontalLine, .5f);
		else
			g.drawDashedLine(horizontalLine, myDash, 2, .5f);
	}

	// List of vertical marker x values
	float freq[26] = { 30.f, 40.f, 50.f, 60.f, 70.f, 80.f, 90.f,
				  100.f, 200.f, 300.f, 400.f, 500.f, 600.f, 700.f, 800.f, 900.f,
				  1000.f, 2000.f, 3000.f, 4000.f, 5000.f, 6000.f, 7000.f, 8000.f,
				  9000.f, 10000.f };

	// Paint vertical parkers
	for (auto i = 0; i < 26; ++i)
	{
		// X scaled for window size and log10 scale
		float markX = (log10(freq[i] * fftSize / fs) - minX) * scaleX;

		// Draw solid lines at 100, 1000 and 10,000
		if (freq[i] == 100 || freq[i] == 1000 || freq[i] == 10000)
		{
			g.drawLine(markX, 0.f, markX, static_cast<float>(getHeight()), .5f);
			g.setColour(juce::Colours::white);
			// Text indicating frequencies
			if (freq[i] == 100)
				g.drawText("100", static_cast<int>(markX - 9), getHeight() - 10, 30, 10, juce::Justification::centred);
			else if (freq[i] == 1000)
				g.drawText("1k", static_cast<int>(markX - 9), getHeight() - 10, 20, 10, juce::Justification::centred);
			else if (freq[i] == 10000)
				g.drawText("10k", static_cast<int>(markX - 9), getHeight() - 10, 30, 10, juce::Justification::centred);

			g.setColour(juce::Colours::white.darker(.8f));
		}
		else
		{
			// Paint line
			g.drawDashedLine(juce::Line<float>(markX, 0.f, markX, static_cast<float>(getHeight())), myDash, 2, 1.f);
		}
	}
}

//==============================================================================

void FilterDisplay::resized()
{
}

//==============================================================================

void FilterDisplay::updateFilter()
{
	// Filter parameters from plugin ValueTree
	auto fc = mAVPTS.getRawParameterValue("FILTER_CUTOFF")->load();
	auto res = mAVPTS.getRawParameterValue("FILTER_RES")->load();
	auto sampleRate = mAVPTS.getRawParameterValue("SAMPLE_RATE")->load();
	int filterType = static_cast<int>(mAVPTS.getRawParameterValue("FILTER_TYPE")->load());

	stateVariableFilter.parameters->setCutOffFrequency(sampleRate, fc, res);

	switch (filterType)
	{
	case 0: stateVariableFilter.parameters->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::lowPass;  break;
	case 1: stateVariableFilter.parameters->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::highPass; break;
	case 2: stateVariableFilter.parameters->type = juce::dsp::StateVariableFilter::Parameters<float>::Type::bandPass; break;
	default: break;
	}
}

//==============================================================================

void FilterDisplay::timerCallback()
{
	// Repaint filter magnitude response if filter parameters have changed.
	auto fc = mAVPTS.getRawParameterValue("FILTER_CUTOFF")->load();
	auto res = mAVPTS.getRawParameterValue("FILTER_RES")->load();
	int filterType = static_cast<int>(mAVPTS.getRawParameterValue("FILTER_TYPE")->load());

	// Check if values have changed
	if (fc != mOldFc || res != mOldRes || filterType != mOldFilterType)
	{
		updateFilter();
		calcMagResponse();
		repaint();
	}
	// Current values as old values
	mOldFc = fc;
	mOldRes = res;
	mOldFilterType = filterType;
}

//==============================================================================

void FilterDisplay::calcMagResponse()
{
	// Create impulse
	juce::zeromem(mImpulse, sizeof(mImpulse));
	mImpulse[0] = 1;
	juce::zeromem(mFilteredImpulse, sizeof(mFilteredImpulse));

	// Filter impulse
	for (auto i = 0; i < fftSize; ++i)
	{
		mFilteredImpulse[i] = stateVariableFilter.processSample(mImpulse[i]);
	}
	// Perform fft
	mFFT.performFrequencyOnlyForwardTransform(mFilteredImpulse);
}