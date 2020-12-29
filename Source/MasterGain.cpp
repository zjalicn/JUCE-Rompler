/*
  ==============================================================================

    MasterGain.cpp
    Created: 28 Dec 2020 3:57:10pm
    Author:  nzjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MasterGain.h"

//==============================================================================
MasterGain::MasterGain(juce::AudioProcessorValueTreeState& vt) : mAVPTS(vt)
{
    setSize(200, 200);

    // GAIN_IN
    // Slider
    mGainInSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mGainInSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 14);
    mGainInSlider.setLookAndFeel(&dialLookAndFeel);
    mGainInSlider.setTextValueSuffix(" dB");

    addAndMakeVisible(&mGainInSlider);
    mGainInAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mAVPTS, "GAIN_IN", mGainInSlider);

    // Label
    mGainInLabel.setFont(10.0f);
    mGainInLabel.setText("Master Gain In", juce::NotificationType::dontSendNotification);
    mGainInLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    mGainInLabel.setJustificationType(juce::Justification::centredTop);
    mGainInLabel.attachToComponent(&mGainInSlider, false);

    // GAIN_OUT
    // Slider
    mGainOutSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mGainOutSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 14);
    mGainOutSlider.setLookAndFeel(&dialLookAndFeel);
    mGainOutSlider.setTextValueSuffix(" dB");

    addAndMakeVisible(&mGainOutSlider);
    mGainOutAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(mAVPTS, "GAIN_OUT", mGainOutSlider);

    // Label
    mGainOutLabel.setFont(10.0f);
    mGainOutLabel.setText("Master Gain Out", juce::NotificationType::dontSendNotification);
    mGainOutLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    mGainOutLabel.setJustificationType(juce::Justification::centredTop);
    mGainOutLabel.attachToComponent(&mGainOutSlider, false);

}

MasterGain::~MasterGain()
{
}

void MasterGain::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::grey.darker());
}

void MasterGain::resized()
{
    const auto startX = 0.0f;
    const auto startY = 0.1f;
    const auto dialWidth = 0.9f;
    const auto dialHeight = 0.4f;

    mGainInSlider.setBoundsRelative(startX, startY, dialWidth, dialHeight);
    mGainOutSlider.setBoundsRelative(startX, startY + dialHeight + 0.1f, dialWidth, dialHeight);
}