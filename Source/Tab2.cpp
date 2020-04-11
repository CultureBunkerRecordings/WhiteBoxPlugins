/*
  ==============================================================================

    Tab2.cpp
    Created: 20 Dec 2019 3:10:30pm
    Author:  William Eden

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Tab2.h"

//==============================================================================
Tab2::Tab2(CompressorTarrAudioProcessor& p): tab1(p), trans(p), processor(p)
{ 
    addAndMakeVisible(trans);
    
    abs.setColour(TextButton::textColourOffId, juce::Colours::black);
    abs.setButtonText("abs");
    abs.setBounds(75, 250, 50, 50);
    addAndMakeVisible(abs);
    
    dB.setColour(TextButton::textColourOffId, juce::Colours::black);
    dB.setButtonText("dB");
    dB.setBounds(150, 250, 50, 50);
    addAndMakeVisible(dB);
//
    gainComputer.setColour(TextButton::textColourOffId, juce::Colours::black);
    gainComputer.setButtonText("Gain Computer");
    gainComputer.setBounds(225, 225, 100, 100);
    addAndMakeVisible(gainComputer);
//
    levelDetector.setColour(TextButton::textColourOffId, juce::Colours::black);
    levelDetector.setButtonText("Level Detector");
    levelDetector.setBounds(425, 225, 100, 100);
    addAndMakeVisible(levelDetector);
//
    lin.setColour(TextButton::textColourOffId, juce::Colours::black);
    lin.setButtonText("lin");
    lin.setBounds(625, 250, 50, 50);
    addAndMakeVisible(lin);
    
    T.addListener(this);
    T.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    T.setBounds(225, 325, 25, 25);
    T.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    T.setRange(-64.0f, 0.0f); 
    T.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    T.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(T);
    
}

Tab2::~Tab2()
{
}

void Tab2::paint (Graphics& g)
{
    g.fillAll (Colours::whitesmoke);   // clear the background

    g.setColour (Colours::black);
    
    Path p1;
    Path p2;
    
    p1.startNewSubPath(25, 200);
    p1.lineTo(725, 200);
    
    p2.startNewSubPath(50, 200);
    p2.lineTo(50, 275);
    p2.lineTo(700, 275);
    p2.lineTo(700, 200);
    
    g.strokePath(p1, PathStrokeType(2));
    g.strokePath(p2, PathStrokeType(2));
    
    g.setColour(Colours::white);
    g.fillEllipse(350, 250, 50, 50);
    g.fillEllipse(550, 250, 50, 50);
       // draw some placeholder text
}

void Tab2::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void Tab2::sliderValueChanged(Slider* slider)
{
    
}

