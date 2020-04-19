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
                                   Timer
{
public:
    TransferFunction(CompressorTarrAudioProcessor&); 
    ~TransferFunction();
    
    TransferFunction& operator=(const TransferFunction &other){
        xAxisThresh = other.xAxisThresh;
        xKnee = other.xKnee;
        xAxisInput = other.xAxisInput;
        yAxisRatio = other.yAxisRatio;
        
        xComp = other.xComp;
        yComp = other.yComp;
        
        
        return *this;
    }
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    
    float xAxisThresh;
    float xKnee;
    float xAxisInput;
    float yAxisRatio;
    
    float xComp; 
    float yComp;

    float paintOutX;
    float paintOutY;
    
    CompressorTarrAudioProcessor& processor;
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransferFunction)
};
