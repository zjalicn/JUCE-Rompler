/*
  ==============================================================================

    MasterGain.h
    Created: 28 Dec 2020 3:57:10pm
    Author:  nzjal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DialLookAndFeel.h"

//==============================================================================
/*
*/
class MasterGain : public juce::Component
{
public:
	MasterGain(juce::AudioProcessorValueTreeState& vt);
	~MasterGain();

	void paint(juce::Graphics&) override;
	void resized() override;


private:
	// Reference of plugin parameters
	juce::AudioProcessorValueTreeState& mAVPTS;
	DialLookAndFeel dialLookAndFeel;

	juce::Slider mGainInSlider, mGainOutSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mGainInAttachment, mGainOutAttachment;
	juce::Label mGainInLabel, mGainOutLabel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MasterGain)
};