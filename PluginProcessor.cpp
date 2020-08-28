/*
  ==============================================================================
 Circular buffer created with the aid of tutorials from The Audio Programmer
 - a lot was left unexplained and was not implemented into any GUI, so
 the values and GUI values were interpreted and implemented by Rob Salino.
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DubEchoAudioProcessor::DubEchoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    delaylength = 0;
    decayratedelay = 0;
    drywetdelay = 0.5;
    
    roomsize = 0;
    decayratereverb = 0.5;
    drywetreverb = 0;
    width = 0.3;
    
    reverbParameters = reverb.getParameters();
    reverbParameters.dryLevel = 0;
    reverbParameters.width = 0.3;
    reverbParameters.damping = 0.5;
    reverbParameters.roomSize = 0.0;
    
}

DubEchoAudioProcessor::~DubEchoAudioProcessor()
{
}

//==============================================================================
const String DubEchoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DubEchoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DubEchoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DubEchoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DubEchoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DubEchoAudioProcessor::getNumPrograms()
{
    return 1;
}

int DubEchoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DubEchoAudioProcessor::setCurrentProgram (int index)
{
}

const String DubEchoAudioProcessor::getProgramName (int index)
{
    return {};
}

void DubEchoAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DubEchoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const int numInputChannels = getTotalNumInputChannels();
    const int delayBufferSize = 2 * (sampleRate + samplesPerBlock);
    mSampleRate = sampleRate;
    
    mDelayBuffer.setSize(numInputChannels, delayBufferSize);
}

void DubEchoAudioProcessor::releaseResources()
{
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DubEchoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DubEchoAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    const int bufferLength = buffer.getNumSamples();
    const int delayBufferLength = mDelayBuffer.getNumSamples();
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        const float* bufferData = buffer.getReadPointer(channel);
        const float* delayBufferData = mDelayBuffer.getReadPointer(channel);
        float* dryBuffer = buffer.getWritePointer(channel);
        
        fillDelayBuffer(channel, bufferLength, delayBufferLength, bufferData, delayBufferData);
        getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData);
        feedbackDelay(channel, bufferLength, delayBufferLength, dryBuffer);
    }
    
    mWritePosition += bufferLength;
    mWritePosition %= delayBufferLength;
    
    //reverb:
    reverbParameters.roomSize = roomsize;
    reverbParameters.damping = decayratereverb;
    reverbParameters.wetLevel = drywetreverb;
    reverbParameters.dryLevel = 1 - drywetreverb;
    reverbParameters.width = width;
    reverb.setParameters(reverbParameters);
        float* leftreverb = buffer.getWritePointer(0);
        float* rightreverb = buffer.getWritePointer(1);
    reverb.processStereo(leftreverb, rightreverb, bufferLength);
}

void DubEchoAudioProcessor::fillDelayBuffer (int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
    
    //copy data from main buffer to delay buffer
    if (delayBufferLength > bufferLength + mWritePosition)
    {
        mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferLength, drywetdelay, drywetdelay);
    }
    else
    {
        const int bufferRemaining = delayBufferLength - mWritePosition;
        
        mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferRemaining, drywetdelay, drywetdelay);
        mDelayBuffer.copyFromWithRamp(channel, 0, bufferData, bufferLength - bufferRemaining, drywetdelay, drywetdelay);
    }
    
}

void DubEchoAudioProcessor::getFromDelayBuffer (AudioBuffer<float>& buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
    int delayTime = delaylength;
    const int readPosition = static_cast<int> (delayBufferLength + mWritePosition - (mSampleRate * delayTime / 1000)) % delayBufferLength;
    
    if (delayBufferLength > bufferLength + readPosition)
    {
        buffer.copyFrom(channel, 0, delayBufferData + readPosition, bufferLength);
    }
    else
    {
        const int bufferRemaining = delayBufferLength - readPosition;
        buffer.copyFrom(channel, 0, delayBufferData + readPosition, bufferRemaining);
        buffer.copyFrom(channel, bufferRemaining, delayBufferData, bufferLength - bufferRemaining);
    }
    
}

void DubEchoAudioProcessor::feedbackDelay (int channel, const int bufferLength, const int delayBufferLength, float* dryBuffer)
{
    if (delayBufferLength > bufferLength + mWritePosition)
    {
        mDelayBuffer.addFromWithRamp(channel, mWritePosition, dryBuffer, bufferLength, decayratedelay, decayratedelay);
    }
    else
    {
        const int bufferRemaining = delayBufferLength - mWritePosition;
        mDelayBuffer.addFromWithRamp(channel, bufferRemaining, dryBuffer, bufferRemaining, decayratedelay, decayratedelay);
        mDelayBuffer.addFromWithRamp(channel, 0, dryBuffer, bufferLength - bufferRemaining, decayratedelay, decayratedelay);
    }
    
}

//==============================================================================
bool DubEchoAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* DubEchoAudioProcessor::createEditor()
{
    return new DubEchoAudioProcessorEditor (*this);
}

//==============================================================================
void DubEchoAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    
}

void DubEchoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DubEchoAudioProcessor();
}
