/*
  ==============================================================================

    Filter.h
    Created: 26 Dec 2020 3:47:31pm
    Author:  nzjal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "DialLookAndFeel.h"
#include "FilterDisplay.h"

//==============================================================================
/*
*/
class Filter : public juce::Component
{
public:
    Filter(TestRomplerAudioProcessor& p);
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    DialLookAndFeel dialLookAndFeel;

    FilterDisplay mFilterDisplay;

    juce::Slider filterCutoffSlider, filterResSlider;
    juce::ComboBox filterTypeMenu;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttachment, filterResAttachment;
    juce::Label filterCutoffLabel, filterResLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;

    TestRomplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
