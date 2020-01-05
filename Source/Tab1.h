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
    void timerCallback() override{
        trans.yAxisThresh = jmap<float>(getAxisThresh(), -64.0f, 0.0f, 0.0f, 1.0f);
        trans.xAxisThresh = jmap<float>(getAxisThresh(), -64.0f, 0.0f, 0.0f, 1.0f);
        trans.yAxisRatio = getRatioValue();
        trans.yKnee = jmap<float>(getKneeValue(), 0, 10, 1, 0); 
        trans.xKnee = jmap<float>(getKneeValue(), 0, 10, 0.0f, 1.0f);
        trans.xAxisInput = jmap<float>(getInputValue(),-48.0f, 12.0f, 400, 0);
        trans.yAxisInput = jmap<float>(getInputValue(), -48.0f, 12.0f, 150, 0);
        trans.repaint(); 
    };
    
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
    
          // not a type -- issue unresolved 
    
    CompressorTarrAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Tab1)
};


