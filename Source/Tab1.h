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
    
    String inputMessage = "Input";
    String outputMessage = "Output";
    String mixMessage = "Mix";
    String threshMessage = "Threshold";
    String ratioMessage = "Ratio";
    String attackMessage = "attack";
    String kneeMessage = "Knee";
    String releaseMessage = "Release";
    String hpfMessage = "High Pass Filter";
    
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


