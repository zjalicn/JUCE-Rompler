/*
  ==============================================================================

    Distortion.h
    Created: 7 Jan 2021 8:38:37pm
    Author:  nzjal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "DialLookAndFeel.h"

//==============================================================================
/*
*/
class Distortion : public juce::Component
{
public:
	Distortion(TestRomplerAudioProcessor& p);
	~Distortion();
	//void prepare(juce::dsp::ProcessSpec);
	//void reset();

	//void process(juce::dsp::ProcessContextReplacing<float> block);
	//void updateParameters();

	void paint(juce::Graphics&) override;
	void resized() override;


private:
	DialLookAndFeel dialLookAndFeel;

	//juce::AudioProcessorValueTreeState& mAVPTS;

	//static constexpr size_t numWaveShapers = 1;
	//juce::dsp::WaveShaper<float> mWaveShapers[numWaveShapers];
	//std::unique_ptr<juce::dsp::Oversampling<float>> mOversampling;

	juce::Slider mDistortionInSlider, mDistortionOutSlider, mDistInFilterSlider;
	juce::Label mDistortionInLabel, mDistortionOutLabel, mDistInFilterLabel;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDistortionInAttachment, mDistortionOutAttachment, mDistInFilterAttachment;
	//juce::dsp::Gain<float> mDistortionInVolume, mDistortionOutVolume;

	//juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> mDistInFilter;
	//float mSampleRate = 44100.f;
	//juce::uint32 mMaxBlockSize = 512;
	//juce::uint32 mNumChannels = 2;

	TestRomplerAudioProcessor& audioProcessor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Distortion)
};