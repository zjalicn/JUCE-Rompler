/*
  ==============================================================================

    Filter.cpp
    Created: 26 Dec 2020 3:47:31pm
    Author:  nzjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter.h"

//==============================================================================
Filter::Filter(TestRomplerAudioProcessor& p) : audioProcessor(p), mFilterDisplay(p.getValueTree())
{
    setSize(200, 200);

    //MAGNITUDE VIEW
    addAndMakeVisible(mFilterDisplay);

    //FILTER_TYPE
    filterTypeMenu.addItem("Low Pass", 1);
    filterTypeMenu.addItem("High Pass", 2);
    filterTypeMenu.addItem("Band Pass", 3);

    filterTypeMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&filterTypeMenu);
    filterTypeAttachment = std::make_unique <juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.getValueTree(), "FILTER_TYPE", filterTypeMenu);

    // FILTER_CUTOFF
    // Slider
    filterCutoffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    filterCutoffSlider.setLookAndFeel(&dialLookAndFeel);
    filterCutoffSlider.setRange(20.0f, 20000.0f);
    filterCutoffSlider.setValue(20000.0f);
    filterCutoffSlider.setTextValueSuffix(" Hz");
    addAndMakeVisible(&filterCutoffSlider);
    filterCutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(), "FILTER_CUTOFF", filterCutoffSlider);
    
    // Label
    filterCutoffLabel.setFont(10.0f);
    filterCutoffLabel.setText("Cutoff", juce::NotificationType::dontSendNotification);
    filterCutoffLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterCutoffLabel.setJustificationType(juce::Justification::centredTop);
    filterCutoffLabel.attachToComponent(&filterCutoffSlider, false);

    // FILTER_RES
    // Slider
    filterResSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterResSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    filterResSlider.setLookAndFeel(&dialLookAndFeel);
    filterResSlider.setRange(1.0f, 5.0f);
    filterResSlider.setValue(1.0f);
    addAndMakeVisible(&filterResSlider);
    filterResAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(), "FILTER_RES", filterResSlider);
    
    // Label
    filterResLabel.setFont(10.0f);
    filterResLabel.setText("Resonance", juce::NotificationType::dontSendNotification);
    filterResLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterResLabel.setJustificationType(juce::Justification::centredTop);
    filterResLabel.attachToComponent(&filterResSlider, false);

}

Filter::~Filter()
{
}

void Filter::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightslategrey.darker());
}

void Filter::resized()
{
    const auto startX = 0.5f;
    const auto startY = 0.2f;
    const auto dialWidth = 0.125f;
    const auto dialHeight = 0.8f;

    mFilterDisplay.setBoundsRelative(0.025f, 0.1f, 0.4f, 0.8f);

    filterTypeMenu.setBoundsRelative(0.45f, 0.4f, dialWidth * 2 + 0.025f, 0.2f);

    filterCutoffSlider.setBoundsRelative(startX + (dialWidth * 2), startY, dialWidth, dialHeight);
    filterResSlider.setBoundsRelative(startX + (dialWidth * 3), startY, dialWidth, dialHeight);
}
