/*
 ==============================================================================

   This file contains the basic framework code for a JUCE plugin processor.

 ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestRomplerAudioProcessorEditor::TestRomplerAudioProcessorEditor (TestRomplerAudioProcessor& p)
    : AudioProcessorEditor (&p), mWaveformDisplay(p), mADSR(p), mFilter(p), audioProcessor (p)
{

    addAndMakeVisible(mWaveformDisplay);
    addAndMakeVisible(mADSR);
    addAndMakeVisible(mFilter);
    setSize(600, 600);

    //startTimerHz(30);
}

TestRomplerAudioProcessorEditor::~TestRomplerAudioProcessorEditor()
{
    //stopTimer();
}

//==============================================================================
void TestRomplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void TestRomplerAudioProcessorEditor::resized()
{
    mWaveformDisplay.setBoundsRelative(0.0f, 0.0f, 1.0f, 0.2f);
    mADSR.setBoundsRelative(0.0f, 0.2f, 1.0f, 0.2f);
    mFilter.setBoundsRelative(0.0f, 0.4f, 1.0f, 0.2f);
}

void TestRomplerAudioProcessorEditor::timerCallback() {
    repaint();
}