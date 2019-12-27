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
#include "Tab1.h"
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
    
private:
    int xAxis, yAxis;
    
    CompressorTarrAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransferFunction)
};
