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
//==============================================================================
/*
*/

class Tab1    : public Component,
                       Slider::Listener,
                       Button::Listener
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
    
    float* getAxisSlider(){
        *ptrThresh = threshSlider.getValue();
        return ptrThresh;
    };
    
private:
    float* ptrThresh;
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


