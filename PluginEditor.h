/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DubEchoAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
{
public:
    DubEchoAudioProcessorEditor (DubEchoAudioProcessor&);
    ~DubEchoAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    LookAndFeel_V4 otherLookAndFeel;
    DubEchoAudioProcessor& processor;

    
    Slider drywetdelaySlider;
    Slider delaylengthSlider;
    Slider decayratedelaySlider;

    Slider drywetreverbSlider;
    Slider roomsizeSlider;
    Slider decayratereverbSlider;
    Slider reverbwidthSlider;
    
    
    Label pluginLabel;
    
    Label delayLabel;
    Label delaylengthLabel;
    Label decayratedelayLabel;
    Label drywetdelayLabel;
    
    Label reverbLabel;
    Label roomsizeLabel;
    Label decayratereverbLabel;
    Label drywetreverbLabel;
    Label reverbwidthLabel;

    
    void sliderValueChanged (Slider* slider) override;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DubEchoAudioProcessorEditor)
};
