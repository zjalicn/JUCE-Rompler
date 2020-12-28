/*
  ==============================================================================

    EnvelopeDisplay.cpp
    Created: 28 Dec 2020 4:51:20am
    Author:  nzjal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "EnvelopeDisplay.h"

EnvelopeDisplay::EnvelopeDisplay(juce::AudioProcessorValueTreeState& vt) : mAVPTS(vt)
{
	// Timer to update filter magnitude response graph
	startTimer(5);
}

EnvelopeDisplay::~EnvelopeDisplay()
{
	// Empty destructor
}

void EnvelopeDisplay::paint(juce::Graphics& g)
{
	// Rounded rectangle around the graph with same but darker colour as the background
	g.setColour(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId).darker(.8f));
	g.fillRoundedRectangle(0.f, 0.f, static_cast<float>(getWidth()), static_cast<float>(getHeight()), 10.f);   // draw an outline around the component
}

//==============================================================================

void EnvelopeDisplay::resized()
{
}

//==============================================================================

void EnvelopeDisplay::updateEnvelope()
{
}

void EnvelopeDisplay::drawEnvelope()
{
}

//==============================================================================

void EnvelopeDisplay::timerCallback()
{
}