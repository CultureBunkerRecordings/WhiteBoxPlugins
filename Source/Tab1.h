/*
  ==============================================================================

    Tab1.h
    Created: 18 Dec 2019 12:48:13pm
    Author:  William Eden

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "dial.h"
#include "PluginProcessor.h"
#include "TransferFunction.h"
//==============================================================================
/*
*/

class Tab1    : public Component,
                       Slider::Listener,
                       Button::Listener,
                       Timer
{
public:
    Tab1(CompressorTarrAudioProcessor&);
    ~Tab1();  

    void paint (Graphics&) override;
    void resized() override;
    void paintDialBackground(Graphics& g, int x, int y, int width, int height);
    void paintMixDialBackground(Graphics& g);
    void sliderValueChanged(Slider* slider) override;
    void buttonClicked (Button* button) override; // [2]
    
    float getKneeValue(){
        knee = kneeSlider.getValue();
        return knee;
    }
    
    float getAxisThresh(){
        thresh = threshSlider.getValue();
        return thresh;
    };
    
    float getRatioValue(){
        ratio = ratioSlider.getValue();
        return ratio;
    }
    
    float getInputValue(){
        input = inputSlider.getValue(); 
        return input;
    }
    void timerCallback() override;
    
private:
    TransferFunction trans;
    int count;
    float thresh;
    float ratio;
    float knee;
    float input;
 
    Slider inputSlider;
    Slider outputSlider;
    Slider mixSlider;
    Slider threshSlider;
    Slider ratioSlider;
    Slider kneeSlider;
    Slider attackSlider;
    Slider releaseSlider;
    Slider hpfSlider;
    TextButton whiteBox;
    TextButton help; 
    
    String inputMessage = "This controlls the level of input to the compressor";
    String outputMessage = "This controls the level of the compressors output";
    String mixMessage = "This controls how much of the compressed signal acts on the output";
    String threshMessage = "This control dictates the level at which the compressor starts to act on the signal";
    String ratioMessage = "The ratio at which compression occurs, ie. with a ratio of 2/1; for every dB over the threshold there is a reduction of 2dB";
    String attackMessage = "This controls how soon the compressor starts acting on the signal";
    String kneeMessage = "This controls the transission from no compression to comression at the threshold, a high value gives a smoother transition (soft knee)";
    String releaseMessage = "This controls how soon the compressor stops acting on the signal";
    String hpfMessage = "This applies a side chained high pass filter to the compressed signal, which allows frequencies above the cut-off frequency to be unaffected by the compression";
    
    BubbleMessageComponent inputHelp;
    BubbleMessageComponent outputHelp;
    BubbleMessageComponent mixHelp;
    BubbleMessageComponent threshHelp;
    BubbleMessageComponent ratioHelp;
    BubbleMessageComponent kneeHelp;
    BubbleMessageComponent attackHelp;
    BubbleMessageComponent releaseHelp;
    BubbleMessageComponent hpfHelp;
    
    MouseListener click;
          // not a type -- issue unresolved 
    
    CompressorTarrAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Tab1)
};


