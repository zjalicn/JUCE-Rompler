/*
  ==============================================================================

    DialLookAndFeel.h
    Created: 27 Dec 2020 8:57:23pm
    Author:  nzjal

  ==============================================================================
*/

// Credits to https://github.com/joonastuo/Filter

#pragma once

#include <JuceHeader.h>
#define _USE_MATH_DEFINES
#include <math.h>

class DialLookAndFeel : public juce::LookAndFeel_V4
{
public:
	void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override
	{
		auto radius = juce::jmin(width / 2, height / 2) - 5.0f;
		auto centreX = x + width * 0.5f;
		auto centreY = y + radius + 12.f;

		// current angle of the slider
		auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

		// Draw path of the slider backgound (in darker background colour)
		juce::Path backgroundArc;
		backgroundArc.addCentredArc(centreX, centreY, radius, radius, 0.0f, rotaryStartAngle, rotaryEndAngle, true);

		juce::Colour myColour = findColour(0x1005700);
		myColour = myColour.darker(.8f);

		g.setColour(myColour);
		g.strokePath(backgroundArc, juce::PathStrokeType(3.f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

		// Draw path of slider foreground (in white)
		juce::Path foregroundArc;
		foregroundArc.addCentredArc(centreX, centreY, radius, radius, 0.0f, rotaryStartAngle, angle, true);
		g.setColour(juce::Colours::white);
		g.strokePath(foregroundArc, juce::PathStrokeType(3.f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

		// Pointer
		juce::Path p;
		auto pointerLength = radius * 1.f;
		auto pointerThickness = 3.0f;
		p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
		p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
		g.fillPath(p);
	}

	// Slider textbox
	void drawLabel(juce::Graphics& g, juce::Label& label) override
	{
		g.setColour(juce::Colours::white);
		juce::String text = label.getText();
		int width = label.getWidth();
		int height = label.getHeight();
		g.setFont(juce::Font(static_cast<float>(height - 2), juce::Font::plain));
		g.drawFittedText(text, 0, 0, width, height, juce::Justification::centred, 1);
	}
};