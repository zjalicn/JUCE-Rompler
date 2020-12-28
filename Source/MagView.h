/*
  ==============================================================================

    MagView.h
    Created: 28 Dec 2020 12:05:56am
    Author:  nzjal

  ==============================================================================
*/

// Credits to https://github.com/joonastuo/Filter

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MagView : public juce::Component, 
				public juce::Timer
{
public:
	MagView(juce::AudioProcessorValueTreeState& vt);
	~MagView();

	void paint(juce::Graphics&) override;
	void paintMarkers(juce::Graphics& g, float scaleX, float minX, float fs);
	void resized() override;
	void updateFilter();
	void timerCallback() override;
	void calcMagResponse();
	enum
	{
		fftOrder = 14,
		fftSize = 1 << fftOrder
	};

private:
	// Reference of plugin parameters
	juce::AudioProcessorValueTreeState& mAVPTS;

	// Filter to draw magnitude impulse response
	juce::dsp::StateVariableFilter::Filter<float> stateVariableFilter;
	juce::dsp::FFT mFFT;

	float mImpulse[fftSize] = { 0.0f };
	float mFilteredImpulse[fftSize * 2] = { 0.0f };

	float mOldFc = 0;
	float mOldRes = 0;
	float mOldFilterType = -1;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MagView)
};