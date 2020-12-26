/*
  ==============================================================================

    WaveformDisplay.h
    Created: 25 Dec 2020 11:23:24pm
    Author:  nzjal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public juce::FileDragAndDropTarget
{
public:
    WaveformDisplay (TestRomplerAudioProcessor& p);
    ~WaveformDisplay() override;

    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    std::vector<float> mAudioPoints;
    juce::String mFileName{ "" };

    TestRomplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
