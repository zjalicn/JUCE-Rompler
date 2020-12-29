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
	// Timer to update ADSR graph
	startTimer(10);
}

EnvelopeDisplay::~EnvelopeDisplay()
{
	// Empty destructor
}

void EnvelopeDisplay::paint(juce::Graphics& g)
{
	// Rounded rectangle around the graph with same but darker colour as the background
	g.setColour(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId).darker(.8f));
	g.fillRoundedRectangle(0.f, 0.f, static_cast<float>(getWidth()), static_cast<float>(getHeight()), 3.f);   // draw an outline around the component

	// Path of the frequency response
	juce::Path myPath;
	// Path colour
	g.setColour(juce::Colours::white);

	// Bottom left of env display
	myPath.startNewSubPath(1.0f, getHeight() - 1.0f);

	//first top left point for attack
	auto attackX = (getWidth() / 3) * (mAVPTS.getRawParameterValue("ATTACK")->load() / 5.0f) + 1.f;
	auto attackY = 10.0f;

	// these work together for the second ADSR point
	auto decayX = attackX + ((getWidth() / 3) * (mAVPTS.getRawParameterValue("DECAY")->load() / 3.0f)) + 1.f;
	auto sustainY = attackY + ((getHeight() - 10.0f) * std::abs((mAVPTS.getRawParameterValue("SUSTAIN")->load() / 1.0f) - 1.0f)) - 1.0f;

	// bottom right point
	auto releaseX = decayX + ((getWidth() / 3) * (mAVPTS.getRawParameterValue("RELEASE")->load() / 5.0f)) - 1.f;
	auto releaseY = getHeight() - 1.0f;

	auto controlX1 = attackX + ((decayX - attackX) * 0.4f);
	auto controlY1 = attackY + (sustainY - attackY) * 0.95f;
	auto controlX2 = decayX + (releaseX - decayX) * 0.4f;
	auto controlY2 = sustainY + (releaseY - sustainY) * 0.95f;

	myPath.lineTo(attackX, attackY - 1.0f); //subtracting 1.f here because y axis is flipped and sustainY is dependant on attackY
	myPath.quadraticTo(controlX1, controlY1, decayX, sustainY);
	myPath.quadraticTo(controlX2, controlY2, releaseX + 1.f, releaseY);

	// Draw path with curves
	juce::Path roundedPath = myPath.createPathWithRoundedCorners(5.0f);
	g.strokePath(roundedPath, juce::PathStrokeType(2.f));
}

//==============================================================================

void EnvelopeDisplay::resized()
{
}

//==============================================================================

void EnvelopeDisplay::updateEnvelope()
{
}

//==============================================================================

void EnvelopeDisplay::timerCallback()
{
	auto attack = mAVPTS.getRawParameterValue("ATTACK")->load();
	auto decay = mAVPTS.getRawParameterValue("DECAY")->load();
	auto sustain = mAVPTS.getRawParameterValue("SUSTAIN")->load();
	auto release = mAVPTS.getRawParameterValue("RELEASE")->load();

	if (attack != oldAttack || decay != oldDecay || sustain != oldSustain || release != oldRelease)
	{
		repaint();

		oldAttack = attack;
		oldDecay = decay;
		oldSustain = sustain;
		oldRelease = release;
	}
}