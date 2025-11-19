/*
  ==============================================================================

    Tab1.h
    Created: 18 Dec 2019 12:48:13pm
    Author:  William Eden

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "TransferFunction.h"
#include "OtherLookAndFeel.h"

class Tab1 : public juce::Component,
    public juce::Slider::Listener,
    public juce::Button::Listener,
    private juce::Timer
{
public:
    Tab1(CompressorTarrAudioProcessor& p);
    ~Tab1() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(Slider* slider) override;
    void paintDialBackground(Graphics& g, int x, int y, int width, int height);

private:

    OtherLookAndFeel tabLookAndFeel;

    TransferFunction trans;

    // Sliders
    juce::Slider inputSlider, outputSlider, mixSlider;
    juce::Slider threshSlider, ratioSlider, kneeSlider;
    juce::Slider attackSlider, releaseSlider, hpfSlider;

    // Slider attachments
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> threshAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratioAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> kneeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> hpfAttachment;

    // Buttons
    juce::ToggleButton help, phaseInvert;

    bool isClicked = false;
    //*******************************************************************************
    //initialise BubbleMessageComponents for help
    
    BubbleMessageComponent inputHelp;
    BubbleMessageComponent outputHelp;
    BubbleMessageComponent mixHelp;
    BubbleMessageComponent threshHelp;
    BubbleMessageComponent ratioHelp;
    BubbleMessageComponent kneeHelp;
    BubbleMessageComponent attackHelp;
    BubbleMessageComponent releaseHelp;
    BubbleMessageComponent hpfHelp;
    
    //*******************************************************************************
    //message for each BubbleMessageComponent
    
    String inputMessage = "This controlls the level of input to the compressor";
    String outputMessage = "This controls the level of the compressors output";
    String mixMessage = "This controls how much of the compressed signal acts on the output";
    String threshMessage = "This control dictates the level at which the compressor starts to act on the signal";
    String ratioMessage = "The ratio at which compression occurs, ie. with a ratio of 2/1; for every dB over the threshold there is a reduction of 2dB";
    String attackMessage = "This controls how soon the compressor starts acting on the signal";
    String kneeMessage = "This controls the transission from no compression to comression at the threshold, a high value gives a smoother transition (soft knee)";
    String releaseMessage = "This controls how soon the compressor stops acting on the signal";
    String hpfMessage = "This applies a side chained high pass filter to the compressed signal, which allows frequencies above the cut-off frequency to be unaffected by the compression";
    MouseListener click;
          // not a type -- issue unresolved 
    
    CompressorTarrAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Tab1)
};


