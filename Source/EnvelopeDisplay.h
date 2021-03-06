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
	void timerCallback() override;

private:
	// Reference of plugin parameters
	juce::AudioProcessorValueTreeState& mAVPTS;

	float oldAttack = 0.0f;
	float oldDecay = 0.0f;
	float oldSustain = 0.0f;
	float oldRelease = 0.0f;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeDisplay)
};