/*
  ==============================================================================

    FilterComponent.cpp
    Created: 26 Dec 2020 3:47:31pm
    Author:  nzjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(TestRomplerAudioProcessor& p) : audioProcessor(p)
{
    setSize(200, 200);

    filterTypeMenu.addItem("Low Pass", 1);
    filterTypeMenu.addItem("High Pass", 2);
    filterTypeMenu.addItem("Band Pass", 3);

    //Filter Type Menu
    filterTypeMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&filterTypeMenu);
    filterTypeAttachment = std::make_unique <juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.getValueTree(), "FILTER_TYPE", filterTypeMenu);

    //Filter Cutoff
    filterCutoffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutoffSlider.setRange(20.0, 20000.0);
    filterCutoffSlider.setValue(20000.0);
    filterCutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    filterCutoffSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::cadetblue.darker());
    // filterResSlider.setSkewFactorFromMidPoint(1000.0f);
    addAndMakeVisible(&filterCutoffSlider);
    filterCutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(), "FILTER_CUTOFF", filterCutoffSlider);

    filterCutoffLabel.setFont(10.0f);
    filterCutoffLabel.setText("Cutoff", juce::NotificationType::dontSendNotification);
    filterCutoffLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterCutoffLabel.setJustificationType(juce::Justification::centredTop);
    filterCutoffLabel.attachToComponent(&filterCutoffSlider, false);

    //Filter Resonance
    filterResSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterResSlider.setRange(1, 5);
    filterResSlider.setValue(1);
    filterResSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    filterResSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::cadetblue.darker());
    addAndMakeVisible(&filterResSlider);
    filterResAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(), "FILTER_RES", filterResSlider);

    filterResLabel.setFont(10.0f);
    filterResLabel.setText("Resonance", juce::NotificationType::dontSendNotification);
    filterResLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterResLabel.setJustificationType(juce::Justification::centredTop);
    filterResLabel.attachToComponent(&filterResSlider, false);

}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightslategrey.darker());
}

void FilterComponent::resized()
{
    const auto startY = 0.4f;
    const auto dialWidth = 0.5f;
    const auto dialHeight = 0.6f;

    filterTypeMenu.setBoundsRelative(0.0f, 0.0f, 1.0f, 0.15f);
    filterCutoffSlider.setBoundsRelative(0.0f, startY, dialWidth, dialHeight);
    filterResSlider.setBoundsRelative(0.5f, startY, dialWidth, dialHeight);
}
