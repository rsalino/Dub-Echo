/*
  ==============================================================================

    Dub-Echo PluginEditor.cpp
    © Rob Salino 2020

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DubEchoAudioProcessorEditor::DubEchoAudioProcessorEditor (DubEchoAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    auto width = 800;
    auto height = 600;
    setSize(width, height); //default size
    otherLookAndFeel.setColour(Slider::thumbColourId, Colours::darkslategrey);
    
    //plugin title
    pluginLabel.setText("Dub Echo", dontSendNotification);
    pluginLabel.setJustificationType(Justification::horizontallyCentred);
    pluginLabel.setFont(Font("Futura", 60.0f, Font::bold));
    pluginLabel.setColour(Label::textColourId, Colours::lightcoral);
    addAndMakeVisible(pluginLabel);
    
    //**************************************DELAY STUFF BELOW*****************************************

    //delay title
    delayLabel.setText("Delay", dontSendNotification);
    delayLabel.setJustificationType(Justification::horizontallyCentred);
    delayLabel.setFont(Font("Futura", 40.0f, Font::bold));
    delayLabel.setColour(Label::textColourId, Colours::lightsteelblue);
    addAndMakeVisible(delayLabel);
    
    //delay length slider settings:
    delaylengthSlider.setColour(Slider::backgroundColourId, Colours::black);
    delaylengthSlider.setColour(Slider::thumbColourId, Colours::lightyellow);
    delaylengthSlider.setTextBoxStyle (Slider::TextBoxBelow, true, width * 0.15, height * 0.05);
    delaylengthSlider.setTextBoxIsEditable(true);
    delaylengthSlider.setRange(0, 1000, 1);
    delaylengthSlider.setTextValueSuffix(" ms");
    delaylengthSlider.setValue(processor.delaylength);
    addAndMakeVisible(delaylengthSlider);
    delaylengthSlider.addListener(this);
    
    //delay rate label settings:
    delaylengthLabel.setText("Delay Length", dontSendNotification);
    delaylengthLabel.setJustificationType(Justification::horizontallyCentred);
    delaylengthLabel.setFont(Font("Futura", 30.0f, Font::plain));
    delaylengthLabel.setColour(Label::backgroundColourId, Colours::darkslategrey);
    delaylengthLabel.setColour(Label::textColourId, Colours::white);
    addAndMakeVisible(delaylengthLabel);
    
    //decay rate delay slider settings:
    decayratedelaySlider.setColour(Slider::backgroundColourId, Colours::black);
    decayratedelaySlider.setColour(Slider::thumbColourId, Colours::lightcoral);
    decayratedelaySlider.setTextBoxStyle (Slider::TextBoxBelow, true, width * 0.05, height * 0.05);
    decayratedelaySlider.setTextBoxIsEditable(true);
    decayratedelaySlider.setRange(0, 1, 0.01);
    decayratedelaySlider.setValue(processor.decayratedelay);
    addAndMakeVisible(decayratedelaySlider);
    decayratedelaySlider.addListener(this);

    
    //decay rate delay label settings:
    decayratedelayLabel.setText("Decay Rate", dontSendNotification);
    decayratedelayLabel.setJustificationType(Justification::horizontallyCentred);
    decayratedelayLabel.setFont(Font("Futura", 30.0f, Font::plain));
    decayratedelayLabel.setColour(Label::backgroundColourId, Colours::darkslategrey);
    decayratedelayLabel.setColour(Label::textColourId, Colours::white);
    addAndMakeVisible(decayratedelayLabel);
    
    //dry/wet delay slider settings:
    drywetdelaySlider.setSliderStyle (Slider::Rotary);
    drywetdelaySlider.setColour(Slider::backgroundColourId, Colours::black);
    drywetdelaySlider.setColour(Slider::thumbColourId, Colours::turquoise);
    drywetdelaySlider.setTextBoxStyle (Slider::TextBoxBelow, true, width * 0.05, height * 0.05);
    drywetdelaySlider.setTextBoxIsEditable(true);
    drywetdelaySlider.setRange(0, 1, 0.01);
    drywetdelaySlider.setValue(processor.drywetdelay);
    addAndMakeVisible(drywetdelaySlider);
    drywetdelaySlider.addListener(this);

    
    //dry/wet delay label settings:
    drywetdelayLabel.setText("Gain", dontSendNotification);
    drywetdelayLabel.setJustificationType(Justification::horizontallyCentred);
    drywetdelayLabel.setFont(Font("Futura", 30.0f, Font::plain));
    drywetdelayLabel.setColour(Label::backgroundColourId, Colours::darkslategrey);
    drywetdelayLabel.setColour(Label::textColourId, Colours::white);
    addAndMakeVisible(drywetdelayLabel);
    
    //******************************************REVERB STUFF BELOW*************************************
    
    //reverb title
    reverbLabel.setText("Reverb", dontSendNotification);
    reverbLabel.setJustificationType(Justification::horizontallyCentred);
    reverbLabel.setFont(Font("Futura", 40.0f, Font::bold));
    reverbLabel.setColour(Label::textColourId, Colours::lightsteelblue);
    addAndMakeVisible(reverbLabel);
    
    //room size slider settings:
    roomsizeSlider.setColour(Slider::backgroundColourId, Colours::black);
    roomsizeSlider.setColour(Slider::thumbColourId, Colours::lightyellow);
    roomsizeSlider.setTextBoxStyle (Slider::TextBoxBelow, true, width * 0.05, height * 0.05);
    roomsizeSlider.setTextBoxIsEditable(true);
    roomsizeSlider.setRange(0, 1, 0.01);
    roomsizeSlider.setValue(processor.roomsize);
    addAndMakeVisible(roomsizeSlider);
    roomsizeSlider.addListener(this);
    
    //room size label settings:
    roomsizeLabel.setText("Room Size", dontSendNotification);
    roomsizeLabel.setJustificationType(Justification::horizontallyCentred);
    roomsizeLabel.setFont(Font("Futura", 30.0f, Font::plain));
    roomsizeLabel.setColour(Label::backgroundColourId, Colours::darkslategrey);
    roomsizeLabel.setColour(Label::textColourId, Colours::white);
    addAndMakeVisible(roomsizeLabel);
    
    //decay rate reverb slider settings:
    decayratereverbSlider.setColour(Slider::backgroundColourId, Colours::black);
    decayratereverbSlider.setColour(Slider::thumbColourId, Colours::lightcoral);
    decayratereverbSlider.setTextBoxStyle (Slider::TextBoxBelow, true, width * 0.05, height * 0.05);
    decayratereverbSlider.setTextBoxIsEditable(true);
    decayratereverbSlider.setRange(0, 1, 0.01);
    decayratereverbSlider.setValue(processor.decayratereverb);
    addAndMakeVisible(decayratereverbSlider);
    decayratereverbSlider.addListener(this);

    
    //decay rate reverb label settings:
    decayratereverbLabel.setText("Damping", dontSendNotification);
    decayratereverbLabel.setJustificationType(Justification::horizontallyCentred);
    decayratereverbLabel.setFont(Font("Futura", 30.0f, Font::plain));
    decayratereverbLabel.setColour(Label::backgroundColourId, Colours::darkslategrey);
    decayratereverbLabel.setColour(Label::textColourId, Colours::white);
    addAndMakeVisible(decayratereverbLabel);
    
    //dry/wet reverb slider settings:
    drywetreverbSlider.setSliderStyle (Slider::Rotary);
    drywetreverbSlider.setColour(Slider::backgroundColourId, Colours::black);
    drywetreverbSlider.setColour(Slider::thumbColourId, Colours::turquoise);
    drywetreverbSlider.setTextBoxStyle (Slider::TextBoxBelow, true, width * 0.05, height * 0.05);
    drywetreverbSlider.setTextBoxIsEditable(true);
    drywetreverbSlider.setRange(0, 1, 0.01);
    drywetreverbSlider.setValue(processor.drywetreverb);
    addAndMakeVisible(drywetreverbSlider);
    drywetreverbSlider.addListener(this);

    
    //dry/wet reverb label settings:
    drywetreverbLabel.setText("Reverb Dry/Wet", dontSendNotification);
    drywetreverbLabel.setJustificationType(Justification::horizontallyCentred);
    drywetreverbLabel.setFont(Font("Futura", 30.0f, Font::plain));
    drywetreverbLabel.setColour(Label::backgroundColourId, Colours::darkslategrey);
    drywetreverbLabel.setColour(Label::textColourId, Colours::white);
    addAndMakeVisible(drywetreverbLabel);
    
    //reverb width slider settings:
    reverbwidthSlider.setColour(Slider::backgroundColourId, Colours::black);
    reverbwidthSlider.setColour(Slider::thumbColourId, Colours::lightcoral);
    reverbwidthSlider.setTextBoxStyle (Slider::TextBoxBelow, true, width * 0.05, height * 0.05);
    reverbwidthSlider.setTextBoxIsEditable(true);
    reverbwidthSlider.setRange(0, 1, 0.01);
    reverbwidthSlider.setValue(processor.width);
    addAndMakeVisible(reverbwidthSlider);
    reverbwidthSlider.addListener(this);

       
    //dry/wet reverb label settings:
    reverbwidthLabel.setText("Reverb Width", dontSendNotification);
    reverbwidthLabel.setJustificationType(Justification::horizontallyCentred);
    reverbwidthLabel.setFont(Font("Futura", 30.0f, Font::plain));
    reverbwidthLabel.setColour(Label::backgroundColourId, Colours::darkslategrey);
    reverbwidthLabel.setColour(Label::textColourId, Colours::white);
    addAndMakeVisible(reverbwidthLabel);
    
}

DubEchoAudioProcessorEditor::~DubEchoAudioProcessorEditor()
{
}

//==============================================================================
void DubEchoAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::darkslategrey);

}

void DubEchoAudioProcessorEditor::resized()
{
    auto border = 1;
    auto area = getLocalBounds().reduced(border * 4);  // entire area
    auto areaWidth = area.getWidth();
    auto areaHeight = area.getHeight();
    
    auto titleArea = area.removeFromTop(0.15 * areaHeight);
    auto delayArea = area.removeFromLeft(0.5 * areaWidth);
    auto delaytitleArea = delayArea.removeFromTop(0.1 * delayArea.getHeight());
    auto delaylengthlabelArea = delayArea.removeFromTop(0.15 * delayArea.getHeight());
    auto delaylengthsliderArea = delayArea.removeFromTop(0.2 * delayArea.getHeight());
    auto decayratedelaylabelArea = delayArea.removeFromTop(0.2 * delayArea.getHeight());
    auto decayratedelaysliderArea = delayArea.removeFromTop(0.25 * delayArea.getHeight());
    auto drywetdelaylabelArea = delayArea.removeFromTop(0.25 * delayArea.getHeight());
    auto drywetdelaysliderArea = delayArea;
    
    auto reverbArea = area;
    auto reverbtitleArea = reverbArea.removeFromTop(0.1 * reverbArea.getHeight());
    auto roomsizelabelArea = reverbArea.removeFromTop(0.15 * reverbArea.getHeight());
    auto roomsizesliderArea = reverbArea.removeFromTop(0.2 * reverbArea.getHeight());
    
    auto decayratereverblabelArea = reverbArea.removeFromTop(0.2 * reverbArea.getHeight());
    auto decayratereverbsliderArea = reverbArea.removeFromTop(0.25 * reverbArea.getHeight());
    auto reverbwidthlabelArea = decayratereverblabelArea.removeFromLeft(0.5 * decayratereverblabelArea.getWidth());
    auto reverbwidthsliderArea = decayratereverbsliderArea.removeFromLeft(0.5 * decayratereverbsliderArea.getWidth());
    auto drywetreverblabelArea = reverbArea.removeFromTop(0.25 * reverbArea.getHeight());
    auto drywetreverbsliderArea = reverbArea;
    
    
    
    
    
    
    pluginLabel.setBounds(titleArea.reduced(border));
    delayLabel.setBounds(delaytitleArea.reduced(border));
    delaylengthLabel.setBounds(delaylengthlabelArea.reduced(border));
    delaylengthSlider.setBounds(delaylengthsliderArea.reduced(border));
    decayratedelayLabel.setBounds(decayratedelaylabelArea.reduced(border));
    decayratedelaySlider.setBounds(decayratedelaysliderArea.reduced(border));
    drywetdelayLabel.setBounds(drywetdelaylabelArea.reduced(border));
    drywetdelaySlider.setBounds(drywetdelaysliderArea.reduced(border));
    
    reverbLabel.setBounds(reverbtitleArea.reduced(border));
    roomsizeLabel.setBounds(roomsizelabelArea.reduced(border));
    roomsizeSlider.setBounds(roomsizesliderArea.reduced(border));
    decayratereverbLabel.setBounds(decayratereverblabelArea.reduced(border));
    decayratereverbSlider.setBounds(decayratereverbsliderArea.reduced(border));
    reverbwidthLabel.setBounds(reverbwidthlabelArea.reduced(border));
    reverbwidthSlider.setBounds(reverbwidthsliderArea.reduced(border));
    drywetreverbLabel.setBounds(drywetreverblabelArea.reduced(border));
    drywetreverbSlider.setBounds(drywetreverbsliderArea.reduced(border));
    
    
}

void DubEchoAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    //delay sliders:
    if(slider == &delaylengthSlider)
    {
        processor.delaylength = delaylengthSlider.getValue();
    }
    else if(slider == &decayratedelaySlider)
    {
        processor.decayratedelay = decayratedelaySlider.getValue();
    }
    else if(slider == &drywetdelaySlider)
    {
        processor.drywetdelay = drywetdelaySlider.getValue();
    }
    
    //reverb sliders:
    else if(slider == &roomsizeSlider)
    {
        processor.roomsize = roomsizeSlider.getValue();
    }
    else if(slider == &decayratereverbSlider)
    {
        processor.decayratereverb = decayratereverbSlider.getValue();
    }
    else if(slider == &drywetreverbSlider)
    {
        processor.drywetreverb = drywetreverbSlider.getValue();
    }
    else if(slider == &reverbwidthSlider)
    {
        processor.width = reverbwidthSlider.getValue();
    }
}
