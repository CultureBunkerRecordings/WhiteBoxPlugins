/*
  ==============================================================================

    TransferFunction.h
    Created: 20 Dec 2019 10:12:18am
    Author:  William Eden

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/

class TransferFunction    : public Component,
                            public Timer
{
public:
    TransferFunction(CompressorTarrAudioProcessor&);
    ~TransferFunction(); 
    void timerCallback() override {
        if( get ){
            yAxis = get(); 
            repaint();
        }
    };
    void paint (Graphics&) override;
    void resized() override;
    
    
    std::function<float*()> get;
    float* yAxis;
    int count;
    CompressorTarrAudioProcessor& processor; 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransferFunction)
};
