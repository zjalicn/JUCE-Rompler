/*
 ==============================================================================

   This file contains the basic framework code for a JUCE plugin processor.

 ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestRomplerAudioProcessorEditor::TestRomplerAudioProcessorEditor (TestRomplerAudioProcessor& p)
    : AudioProcessorEditor (&p), 
    mWaveformDisplay(p), 
    mGain(p.getValueTree()), 
    mADSR(p), 
    mFilter(p), 
    //mDistortion(p), 
    audioProcessor (p)
{
    addAndMakeVisible(mWaveformDisplay);
    addAndMakeVisible(mGain);
    addAndMakeVisible(mADSR);
    addAndMakeVisible(mFilter);
    //addAndMakeVisible(mDistortion);
    setSize(600, 600);
}

TestRomplerAudioProcessorEditor::~TestRomplerAudioProcessorEditor()
{
}

//==============================================================================
void TestRomplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void TestRomplerAudioProcessorEditor::resized()
{
    mWaveformDisplay.setBoundsRelative(0.0f, 0.0f, 0.8f, 0.2f);
    mGain.setBoundsRelative(0.8f, 0.0f, 0.2f, 0.2f);
    mADSR.setBoundsRelative(0.0f, 0.2f, 1.0f, 0.2f);
    mFilter.setBoundsRelative(0.0f, 0.4f, 1.0f, 0.2f);
    //mDistortion.setBoundsRelative(0.0f, 0.6f, 1.0f, 0.2f);
}

void TestRomplerAudioProcessorEditor::timerCallback() {
    repaint();
}