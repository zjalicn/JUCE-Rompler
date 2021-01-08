/*
  ==============================================================================

    Envelope.h
    Created: 26 Dec 2020 1:46:32am
    Author:  nzjal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "DialLookAndFeel.h"
#include "EnvelopeDisplay.h"

//==============================================================================
/*
*/
class Envelope : public juce::Component
{
public:
    Envelope(TestRomplerAudioProcessor& p);
    ~Envelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    DialLookAndFeel dialLookAndFeel;

    EnvelopeDisplay mEnvDisplay;

    juce::Slider mAttackSlider, mDecaySlider, mSustainSlider, mReleaseSlider;
    juce::Label mAttackLabel, mDecayLabel, mSustainLabel, mReleaseLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mAttackAttachment, mDecayAttachment, mSustainAttachment, mReleaseAttachment;

    TestRomplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
