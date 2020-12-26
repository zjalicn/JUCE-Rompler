/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 25 Dec 2020 11:23:24pm
    Author:  nzjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(TestRomplerAudioProcessor& p) : audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    auto waveform = audioProcessor.getWaveForm();

    g.fillAll(juce::Colours::cadetblue.darker());

    if (waveform.getNumSamples() > 0)
    {
        // Display waveform
        juce::Path p;
        mAudioPoints.clear();
        g.setColour(juce::Colours::white);

        auto ratio = waveform.getNumSamples() / getWidth();
        auto buffer = waveform.getReadPointer(0);

        for (int sample = 0; sample < waveform.getNumSamples(); sample += ratio)
        {
            // try an averaging fn for the last parameter
            // ratio : sample = 44100 (1 sec)...x axis of window = 600 == sampleLength / getWidth()

            mAudioPoints.push_back(buffer[sample]);
        }

        p.startNewSubPath(0.0f, getHeight() / 2.0f);

        for (int sample = 0; sample < mAudioPoints.size(); ++sample)
        {
            // values of audiofile -1 to -... y axis of window is 200... -1 to 1 in audio to mean 200 to 0
            // use the ratio to take values from the audio buffer to put in vector to display
            auto point = juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, getHeight(), 0.0f);
            p.lineTo(sample, point);
        }

        g.strokePath(p, juce::PathStrokeType(2));

        // Display File Name
        g.setColour(juce::Colours::white);
        g.setFont(15.0f);
        auto textBounds = getLocalBounds().reduced(10, 10);
        g.drawFittedText(mFileName, textBounds, juce::Justification::topRight, 1);

        // Display Playhead
        //auto playheadPosition = juce::jmap<int>(audioProcessor.getSampleCount(), 0, audioProcessor.getWaveForm().getNumSamples(), 0, getWidth());
        //g.setColour(juce::Colours::orangered.darker());
        //g.drawLine(playheadPosition, 0, playheadPosition, getHeight(), 2.0f);
    
        //g.setColour(juce::Colours::black.withAlpha(0.2f));
        //g.fillRect(0, 0, playheadPosition, getHeight());
    } 
    else 
    {
        g.setFont(20.0f);
        g.setColour(juce::Colours::white);
        g.drawFittedText("Drop an Audio File to Load", getLocalBounds(), juce::Justification::centred, 1);
    }
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}


bool WaveformDisplay::isInterestedInFileDrag(const juce::StringArray& files)
{
    for (auto file : files)
    {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aiff") || file.contains(".aif"))
        {
            return true;
        }
    }

    return false;
}

void WaveformDisplay::filesDropped(const juce::StringArray& files, int x, int y)
{
    for (auto file : files)
    {
        if (isInterestedInFileDrag(files))
        {
            auto myFile = std::make_unique<juce::File>(file);
            mFileName = myFile->getFileNameWithoutExtension();
            audioProcessor.loadFile(file);
        }
    }
    repaint();
}