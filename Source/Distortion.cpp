/*
  ==============================================================================

    Distortion.cpp
    Created: 7 Jan 2021 8:38:37pm
    Author:  nzjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Distortion.h"

//==============================================================================
Distortion::Distortion(TestRomplerAudioProcessor& p) : audioProcessor(p)
														/*mWaveShapers{ { std::tanh } }, 
														mDistInFilter(juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(44100.f, 20000.f))*/
{
	//mOversampling.reset(new juce::dsp::Oversampling<float>(2, 3, juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR, false));

	// DISTORTION_IN
	// Slider
	mDistortionInSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	mDistortionInSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 14);
	mDistortionInSlider.setLookAndFeel(&dialLookAndFeel);
	addAndMakeVisible(mDistortionInSlider);

	// Label
	mDistortionInLabel.setFont(10.0f);
	mDistortionInLabel.setText("Distortion In", juce::NotificationType::dontSendNotification);
	mDistortionInLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
	mDistortionInLabel.setJustificationType(juce::Justification::centredTop);
	mDistortionInLabel.attachToComponent(&mDistortionInSlider, false);

	mDistortionInAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(), "DISTORTION_IN", mDistortionInSlider);

	// DISTORTION_OUT
	// Slider
	mDistortionOutSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	mDistortionOutSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 14);
	mDistortionOutSlider.setLookAndFeel(&dialLookAndFeel);
	addAndMakeVisible(mDistortionOutSlider);

	// Label
	mDistortionOutLabel.setFont(10.0f);
	mDistortionOutLabel.setText("Distortion Out", juce::NotificationType::dontSendNotification);
	mDistortionOutLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
	mDistortionOutLabel.setJustificationType(juce::Justification::centredTop);
	mDistortionOutLabel.attachToComponent(&mDistortionOutSlider, false);

	mDistortionOutAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(), "DISTORTION_OUT", mDistortionOutSlider);

	// DIST_IN_FILTER
	// Slider
	mDistInFilterSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	mDistInFilterSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 14);
	mDistInFilterSlider.setLookAndFeel(&dialLookAndFeel);
	addAndMakeVisible(mDistInFilterSlider);

	// Label
	mDistInFilterLabel.setFont(10.0f);
	mDistInFilterLabel.setText("Distortion Filter In", juce::NotificationType::dontSendNotification);
	mDistInFilterLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
	mDistInFilterLabel.setJustificationType(juce::Justification::centredTop);
	mDistInFilterLabel.attachToComponent(&mDistInFilterSlider, false);

	mDistInFilterAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getValueTree(), "DIST_IN_FILTER", mDistInFilterSlider);

}

Distortion::~Distortion()
{
	// Empty destructor
}

//void Distortion::prepare(juce::dsp::ProcessSpec spec)
//{
//	mSampleRate = static_cast<float>(spec.sampleRate);
//	mMaxBlockSize = spec.maximumBlockSize;
//	mNumChannels = spec.numChannels;
//
//	mDistortionInVolume.prepare(spec);
//	mDistortionOutVolume.prepare(spec);
//	mDistInFilter.prepare(spec);
//
//	mOversampling->initProcessing(static_cast<size_t> (mMaxBlockSize));
//	reset();
//}
//
//void Distortion::reset()
//{
//	mOversampling->reset();
//	mDistInFilter.reset();
//}

//void Distortion::process(juce::dsp::ProcessContextReplacing<float> context)
//{
//	juce::ScopedNoDenormals noDenormals;
//
//	mDistortionInVolume.process(context);
//
//	mDistInFilter.process(context);
//
//	juce::dsp::AudioBlock<float> oversampledBlock = mOversampling->processSamplesUp(context.getInputBlock());
//	auto waveshaperContext = juce::dsp::ProcessContextReplacing<float>(oversampledBlock);
//
//	mWaveShapers[0].process(waveshaperContext);
//	waveshaperContext.getOutputBlock() *= 0.7f;
//
//	// downsample
//	mOversampling->processSamplesDown(context.getOutputBlock());
//
//	mDistortionOutVolume.process(context);
//}

//void Distortion::updateParameters()
//{
//	float inputVolume = *mAVPTS.getRawParameterValue("DISTORTION_IN");
//	float outputVolume = *mAVPTS.getRawParameterValue("DISTORTION_OUT");
//
//	auto inputdB = juce::Decibels::decibelsToGain(inputVolume);
//	auto outputdB = juce::Decibels::decibelsToGain(outputVolume);
//
//	if (mDistortionInVolume.getGainLinear() != inputdB) mDistortionInVolume.setGainLinear(inputdB);
//	if (mDistortionOutVolume.getGainLinear() != outputdB) mDistortionOutVolume.setGainLinear(outputdB);
//
//	juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> mDistInFilter;
//
//	float freqHiPass = *mAVPTS.getRawParameterValue("DIST_IN_FILTER");
//	*mDistInFilter.state = *juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(mSampleRate, freqHiPass);
//
//}

void Distortion::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::papayawhip.darker());
}

void Distortion::resized()
{
	const auto startX = 0.5f;
	const auto startY = 0.2f;
	const auto dialWidth = 0.125f;
	const auto dialHeight = 0.8f;

	mDistortionInSlider.setBoundsRelative(startX, startY, dialWidth, dialHeight);
	mDistortionOutSlider.setBoundsRelative(startX + dialWidth, startY, dialWidth, dialHeight);
	mDistInFilterSlider.setBoundsRelative(startX + dialWidth * 2, startY, dialWidth, dialHeight);
}