/*
 ==============================================================================

   This file contains the basic framework code for a JUCE plugin processor.

 ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveformDisplay.h"
#include "Envelope.h"
#include "FilterComponent.h"

//==============================================================================
/**
*/
class TestRomplerAudioProcessorEditor : public juce::AudioProcessorEditor,
                                        public juce::Timer
{
public:
    TestRomplerAudioProcessorEditor (TestRomplerAudioProcessor&);
    ~TestRomplerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;

private:
    WaveformDisplay mWaveformDisplay;
    Envelope mADSR;
    FilterComponent mFilter;

    TestRomplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestRomplerAudioProcessorEditor)
};
