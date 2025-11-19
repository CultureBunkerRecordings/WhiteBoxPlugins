/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorTarrAudioProcessorEditor::CompressorTarrAudioProcessorEditor (CompressorTarrAudioProcessor& p)
: /*C(p),*/ AudioProcessorEditor (&p), tabs(TabbedButtonBar::Orientation::TabsAtTop), tab1(p), processor(p)
{ 
    
    //add tab1
    setSize(800, 400);
    tabs.setSize(getWidth(), getHeight());
    tabs.addTab("Compressor", juce::Colours::ghostwhite, &tab1, false);
    tabs.setTabBarDepth(20);
    addAndMakeVisible(tabs);


}

CompressorTarrAudioProcessorEditor::~CompressorTarrAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
};



//==============================================================================
void CompressorTarrAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(juce::Colours::whitesmoke);
   
}

void CompressorTarrAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


