/*
  ==============================================================================

    EnvelopeDisplay.h
    Created: 28 Dec 2020 4:51:20am
    Author:  nzjal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class EnvelopeDisplay : public juce::Component,
						public juce::Timer
{
public:
	EnvelopeDisplay(juce::AudioProcessorValueTreeState& vt);
	~EnvelopeDisplay();

	void paint(juce::Graphics&) override;
	void resized() override;
	void updateEnvelope();
	void drawEnvelope();
	void timerCallback() override;
	enum
	{
		fftOrder = 14,
		fftSize = 1 << fftOrder
	};

private:
	// Reference of plugin parameters
	juce::AudioProcessorValueTreeState& mAVPTS;


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeDisplay)
};