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

class TransferFunction    : public Component
{
public:
    TransferFunction(CompressorTarrAudioProcessor&); 
    ~TransferFunction();
    void paint (Graphics&) override;
    void resized() override; 
    
    float yAxisThresh;
    float xAxisThresh;
    float yAxisRatio;
    float yKnee;
    float xKnee;
    float xAxisInput;
    float yAxisInput;

    float yWitKnee;
    
    float xComp;
    float yComp;

    int count;
    CompressorTarrAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransferFunction)
};
