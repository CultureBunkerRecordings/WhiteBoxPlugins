/*
  ==============================================================================

    Tab2.h
    Created: 20 Dec 2019 3:10:30pm
    Author:  William Eden

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TransferFunction.h"
//==============================================================================
/*
*/
class Tab2    : public Component
{
public:
    Tab2(CompressorTarrAudioProcessor&);
    ~Tab2();

    void paint (Graphics&) override;
    void resized() override;

    //*******************************************************************************
    //member variables
private:
    TransferFunction trans;
    TextButton abs;
    TextButton dB;
    TextButton gainComputer;
    TextButton levelDetector;
    TextButton lin;
    
    CompressorTarrAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Tab2)
};
