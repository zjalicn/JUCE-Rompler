/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 26 Dec 2020 1:46:32am
    Author:  nzjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent(TestRomplerAudioProcessor& p) : audioProcessor (p)
{
    // Attack 
    mAttackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mAttackSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::red);
    addAndMakeVisible(mAttackSlider);

    mAttackLabel.setFont(10.0f);
    mAttackLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    mAttackLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    mAttackLabel.setJustificationType(juce::Justification::centredTop);
    mAttackLabel.attachToComponent(&mAttackSlider, false);

    mAttackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(), "ATTACK", mAttackSlider);

    // Decay
    mDecaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mDecaySlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::red);
    addAndMakeVisible(mDecaySlider);

    mDecayLabel.setFont(10.0f);
    mDecayLabel.setText("Delay", juce::NotificationType::dontSendNotification);
    mDecayLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    mDecayLabel.setJustificationType(juce::Justification::centredTop);
    mDecayLabel.attachToComponent(&mDecaySlider, false);

    mDecayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(), "DECAY", mDecaySlider);

    // Sustain
    mSustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mSustainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::red);
    addAndMakeVisible(mSustainSlider);

    mSustainLabel.setFont(10.0f);
    mSustainLabel.setText("Sustain", juce::NotificationType::dontSendNotification);
    mSustainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    mSustainLabel.setJustificationType(juce::Justification::centredTop);
    mSustainLabel.attachToComponent(&mSustainSlider, false);

    mSustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(), "SUSTAIN", mSustainSlider);

    // Release
    mReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mReleaseSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::red);
    addAndMakeVisible(mReleaseSlider);

    mReleaseLabel.setFont(10.0f);
    mReleaseLabel.setText("Release", juce::NotificationType::dontSendNotification);
    mReleaseLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    mReleaseLabel.setJustificationType(juce::Justification::centredTop);
    mReleaseLabel.attachToComponent(&mReleaseSlider, false);

    mReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(), "RELEASE", mReleaseSlider);

}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void ADSRComponent::resized()
{
    const auto startY = 0.2f;
    const auto dialWidth = 0.15f;
    const auto dialHeight = 0.8f;

    mAttackSlider.setBoundsRelative(0.4f, startY, dialWidth, dialHeight);
    mDecaySlider.setBoundsRelative(0.55f, startY, dialWidth, dialHeight);
    mSustainSlider.setBoundsRelative(0.7f, startY, dialWidth, dialHeight);
    mReleaseSlider.setBoundsRelative(0.85f, startY, dialWidth, dialHeight);
}