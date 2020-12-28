/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 26 Dec 2020 1:46:32am
    Author:  nzjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(TestRomplerAudioProcessor& p) : audioProcessor (p)
{

    // ATTACK
    // Slider
    mAttackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 14);
    mAttackSlider.setLookAndFeel(&dialLookAndFeel);
    addAndMakeVisible(mAttackSlider);

    // Label
    mAttackLabel.setFont(10.0f);
    mAttackLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    mAttackLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    mAttackLabel.setJustificationType(juce::Justification::centredTop);
    mAttackLabel.attachToComponent(&mAttackSlider, false);

    mAttackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(), "ATTACK", mAttackSlider);

    // DECAY
    // Slider
    mDecaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 14);
    mDecaySlider.setLookAndFeel(&dialLookAndFeel);
    addAndMakeVisible(mDecaySlider);

    // Label
    mDecayLabel.setFont(10.0f);
    mDecayLabel.setText("Delay", juce::NotificationType::dontSendNotification);
    mDecayLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    mDecayLabel.setJustificationType(juce::Justification::centredTop);
    mDecayLabel.attachToComponent(&mDecaySlider, false);

    mDecayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(), "DECAY", mDecaySlider);

    // SUSTAIN
    // Slider
    mSustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 14);
    mSustainSlider.setLookAndFeel(&dialLookAndFeel);
    addAndMakeVisible(mSustainSlider);

    // Label
    mSustainLabel.setFont(10.0f);
    mSustainLabel.setText("Sustain", juce::NotificationType::dontSendNotification);
    mSustainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    mSustainLabel.setJustificationType(juce::Justification::centredTop);
    mSustainLabel.attachToComponent(&mSustainSlider, false);

    mSustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(), "SUSTAIN", mSustainSlider);

    // RELEASE
    // Slider
    mReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 14);
    mReleaseSlider.setLookAndFeel(&dialLookAndFeel);
    addAndMakeVisible(mReleaseSlider);

    // Label
    mReleaseLabel.setFont(10.0f);
    mReleaseLabel.setText("Release", juce::NotificationType::dontSendNotification);
    mReleaseLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    mReleaseLabel.setJustificationType(juce::Justification::centredTop);
    mReleaseLabel.attachToComponent(&mReleaseSlider, false);

    mReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(), "RELEASE", mReleaseSlider);

}

Envelope::~Envelope()
{
}

void Envelope::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void Envelope::resized()
{
    const auto startY = 0.2f;
    const auto dialWidth = 0.15f;
    const auto dialHeight = 0.8f;

    mAttackSlider.setBoundsRelative(0.4f, startY, dialWidth, dialHeight);
    mDecaySlider.setBoundsRelative(0.55f, startY, dialWidth, dialHeight);
    mSustainSlider.setBoundsRelative(0.7f, startY, dialWidth, dialHeight);
    mReleaseSlider.setBoundsRelative(0.85f, startY, dialWidth, dialHeight);
}