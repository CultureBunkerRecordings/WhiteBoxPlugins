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
: /*C(p),*/ AudioProcessorEditor (&p), processor (p), tab1(p), tab2(p), tabs(TabbedButtonBar::Orientation::TabsAtTop)
{ 
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    //trying to work out tabs
    
    setSize (800, 400);
    
    //set overriden lookandfeel
    setLookAndFeel(&otherLookAndFeel);
    
    //add tab1 and tab2
    tabs.setSize(getWidth(), getHeight());
    tabs.addTab("myTab", juce::Colours::ghostwhite, &tab1, false);
    tabs.addTab("myTab2", juce::Colours::ghostwhite, &tab2, false);
    tabs.setTabBarDepth(20);
    addAndMakeVisible(tabs);
    
    //set up ffmeter
    lnf = new FFAU::LevelMeterLookAndFeel();
    // adjust the colours to how you like them, e.g.
    lnf->setColour (FFAU::LevelMeter::lmMeterGradientLowColour, juce::Colours::green);
    lnf->setColour(FFAU::LevelMeter::lmOutlineColour, juce::Colours::lightgrey);
    meter = new FFAU::LevelMeter(); // See FFAU::LevelMeter::MeterFlags for options
    meter->setLookAndFeel (lnf);
    meter->setMeterSource (&processor.getMeterSource());
    meter->setBounds(745, 50, 30, getHeight()-75);
    addAndMakeVisible (meter);
    
}

CompressorTarrAudioProcessorEditor::~CompressorTarrAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
};



//==============================================================================
void CompressorTarrAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(juce::Colours::ghostwhite);
   
}

void CompressorTarrAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
