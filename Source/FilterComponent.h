/*
  ==============================================================================

    FilterComponent.h
    Created: 26 Dec 2020 3:47:31pm
    Author:  nzjal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(TestRomplerAudioProcessor& p);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider filterCutoffSlider, filterResSlider;
    juce::ComboBox filterTypeMenu;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttachment, filterResAttachment;
    juce::Label filterCutoffLabel, filterResLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;

    TestRomplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
