/*
  ==============================================================================
    Dub-Echo PluginProcessor.h
    © Rob Salino 2020
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class DubEchoAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    DubEchoAudioProcessor();
    ~DubEchoAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void fillDelayBuffer (int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);
    
    void getFromDelayBuffer (AudioBuffer<float>& buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);
    
    void feedbackDelay (int channel, const int bufferLength, const int delayBufferLength, float* dryBuffer);
    
    float drywetdelay;
    float drywetreverb;
    
    float decayratedelay;
    float decayratereverb;

    int delaylength;
    float roomsize;
    float width;
    
    juce::Reverb reverb;
    juce::Reverb::Parameters reverbParameters;
    

private:
    AudioBuffer<float> mDelayBuffer;
    int mWritePosition { 0 };
    int mSampleRate { 44100 };
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DubEchoAudioProcessor)
};
