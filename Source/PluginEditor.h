/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Tab1.h"
#include "TransferFunction.h"
//==============================================================================
// CompressorTarrAudioProcessorEditor class

class CompressorTarrAudioProcessorEditor  : public AudioProcessorEditor

{
public:
    CompressorTarrAudioProcessorEditor (CompressorTarrAudioProcessor&);
    ~CompressorTarrAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:    
    //TabbedComponent tabs owns classes Tab1 and Tab2.
    TabbedComponent tabs;
    Tab1 tab1;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CompressorTarrAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorTarrAudioProcessorEditor)
};
