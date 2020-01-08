/*
  ==============================================================================

    Tab1.cpp
    Created: 18 Dec 2019 12:48:13pm
    Author:  William Eden

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Tab1.h"

//==============================================================================
Tab1::Tab1(CompressorTarrAudioProcessor& p): processor(p), thresh(0), ratio(0), input(0), knee(0), count(0), trans(p)
{
    Timer::startTimerHz(60);
    
    inputSlider.addListener(this);
    inputSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    inputSlider.setBounds(25, 200, 100, 100);
    inputSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    inputSlider.setRange(-48.0f, 12.0f);
    inputSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    inputSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(inputSlider);
    
    outputSlider.addListener(this);
    outputSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    outputSlider.setBounds(625, 200, 100, 100);
    outputSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    outputSlider.setRange(-48, 12);
    outputSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    outputSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(outputSlider);
    
    mixSlider.addListener(this);
    mixSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    mixSlider.setBounds(325, 200, 100, 100);
    mixSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    mixSlider.setRange(0.0f, 100.0f);
    mixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    mixSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(mixSlider);
    
    threshSlider.addListener(this);
    threshSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    threshSlider.setBounds(125, 225, 75, 75);
    threshSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    threshSlider.setRange(-64.0f, 0.0f);
    threshSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    threshSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(threshSlider);
    
    ratioSlider.addListener(this);
    ratioSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    ratioSlider.setBounds(187.5, 225, 75, 75);
    ratioSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    ratioSlider.setRange(1.0f, 10.0f);
    ratioSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    ratioSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(ratioSlider);
    
    kneeSlider.addListener(this);
    kneeSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    kneeSlider.setBounds(250, 225, 75, 75);
    kneeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    kneeSlider.setRange(0.0f, 10.0f);
    kneeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    kneeSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(kneeSlider);
    
    attackSlider.addListener(this);
    attackSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    attackSlider.setBounds(425, 225, 75, 75);
    attackSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    attackSlider.setRange(0.0f, 1500.0f);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    attackSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(attackSlider);
    
    releaseSlider.addListener(this);
    releaseSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    releaseSlider.setBounds(487.5, 225, 75, 75);
    releaseSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    releaseSlider.setRange(0.0f, 3000.0f);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    releaseSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(releaseSlider);
    //
    hpfSlider.addListener(this);
    hpfSlider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
    hpfSlider.setBounds(550, 225, 75, 75);
    hpfSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    hpfSlider.setRange(0.0f, 500.0f);
    hpfSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    hpfSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(hpfSlider);
    
    whiteBox.addListener(this);
    whiteBox.setBounds(25, 160, 100, 20);
    whiteBox.setButtonText("White Box");
    addAndMakeVisible(whiteBox);
    
    help.setBounds(700, 160, 20, 20);
    help.setButtonText("?");
    addAndMakeVisible(help);
    
    addAndMakeVisible(&trans);
    
    inputSlider.addMouseListener(&click, false);
    inputHelp.setColour(BubbleMessageComponent::backgroundColourId, Colours::white);
    inputHelp.setPosition(&inputSlider);
    
    outputSlider.addMouseListener(&click, false);
    outputHelp.setColour(BubbleMessageComponent::backgroundColourId, Colours::white);
    outputHelp.setPosition(&outputSlider);
    
    mixSlider.addMouseListener(&click, false);
    mixHelp.setColour(BubbleMessageComponent::backgroundColourId, Colours::white);
    mixHelp.setPosition(&mixSlider);
    
    threshSlider.addMouseListener(&click, false);
    threshHelp.setColour(BubbleMessageComponent::backgroundColourId, Colours::white);
    threshHelp.setPosition(&threshSlider);
    
    ratioSlider.addMouseListener(&click, false);
    ratioHelp.setColour(BubbleMessageComponent::backgroundColourId, Colours::white);
    ratioHelp.setPosition(&ratioSlider);
    
    attackSlider.addMouseListener(&click, false);
    attackHelp.setColour(BubbleMessageComponent::backgroundColourId, Colours::white);
    attackHelp.setPosition(&attackSlider);
    
    kneeSlider.addMouseListener(&click, false);
    kneeHelp.setColour(BubbleMessageComponent::backgroundColourId, Colours::white);
    kneeHelp.setPosition(&kneeSlider);
    
    releaseSlider.addMouseListener(&click, false);
    releaseHelp.setColour(BubbleMessageComponent::backgroundColourId, Colours::white);
    releaseHelp.setPosition(&releaseSlider);

    hpfSlider.addMouseListener(&click, false);
    hpfHelp.setColour(BubbleMessageComponent::backgroundColourId, Colours::white);
    hpfHelp.setPosition(&hpfSlider);

}

Tab1::~Tab1()
{
};

void Tab1::timerCallback()
{
    trans.yAxisThresh = jmap<float>(getAxisThresh(), -64.0f, 0.0f, 0.0f, 1.0f);
    trans.xAxisThresh = jmap<float>(getAxisThresh(), -64.0f, 0.0f, 0.0f, 1.0f);
    trans.yAxisRatio = getRatioValue();
    trans.yKnee = jmap<float>(getKneeValue(), 0, 10, 1, 0);
    trans.xKnee = jmap<float>(getKneeValue(), 0, 10, 0.0f, 1.0f);
    trans.xAxisInput = jmap<float>(getInputValue(),-48.0f, 12.0f, 400, 0);
    trans.yAxisInput = jmap<float>(getInputValue(), -48.0f, 12.0f, 150, 0);
    trans.repaint();
    
        
    if (inputSlider.isMouseButtonDown()){
        inputHelp.showAt(&inputSlider,AttributedString(inputMessage), 1000);
        addAndMakeVisible(inputHelp);
    };
    
    if (outputSlider.isMouseButtonDown()){
        outputHelp.showAt(&outputSlider,AttributedString(outputMessage), 1000);
        addAndMakeVisible(outputHelp);
    };
    
    if (mixSlider.isMouseButtonDown()){
        mixHelp.showAt(&mixSlider,AttributedString(mixMessage), 1000);
        addAndMakeVisible(mixHelp);
    };
    
    if (threshSlider.isMouseButtonDown()){
        threshHelp.showAt(&threshSlider,AttributedString(threshMessage), 1000);
        addAndMakeVisible(threshHelp);
    };
    
    if (ratioSlider.isMouseButtonDown()){
        ratioHelp.showAt(&ratioSlider,AttributedString(ratioMessage), 1000);
        addAndMakeVisible(ratioHelp);
    };
    
    if (attackSlider.isMouseButtonDown()){
        attackHelp.showAt(&attackSlider,AttributedString(attackMessage), 1000);
        addAndMakeVisible(attackHelp);
    };
    
    if (kneeSlider.isMouseButtonDown()){
        kneeHelp.showAt(&kneeSlider,AttributedString(kneeMessage), 1000);
        addAndMakeVisible(kneeHelp);
    };
    
    if (releaseSlider.isMouseButtonDown()){
        releaseHelp.showAt(&releaseSlider,AttributedString(releaseMessage), 1000);
        addAndMakeVisible(releaseHelp);
    };
    
    if (hpfSlider.isMouseButtonDown()){
        hpfHelp.showAt(&hpfSlider,AttributedString(hpfMessage), 1000);
        addAndMakeVisible(hpfHelp);
    };
};
    
void Tab1::buttonClicked (Button* button) // [2]
{ 
    if (button == &whiteBox){
    };
    
};
void Tab1::sliderValueChanged(Slider* slider)
{
    if (slider == &inputSlider)
    {
        processor.inputGain = slider->getValue();
    }
    if (slider == &outputSlider)
    {
        processor.outputGain = slider->getValue();
    }
    if (slider == &mixSlider)
    {
        processor.mix = slider->getValue();
    }
    if (slider == &kneeSlider)
    {
        processor.knee = slider->getValue();
    }
    if (slider == &threshSlider)
    {
        processor.T = slider->getValue();
    }
    
    if (slider == &ratioSlider)
    {
        processor.R = slider->getValue();
    }
    
    if (slider == &attackSlider)
    {
        processor.attack = slider->getValue();
    }
    
    if (slider == &releaseSlider)
    {
        processor.release = slider->getValue();
    }
};

void Tab1::paintMixDialBackground(Graphics& g)
{
    Path p1;
    Path p2;
    ColourGradient grade(Colours::green, 325, 125, Colours::red, 425, 125, false);
    g.setColour(Colours::grey);
    p1.addPieSegment(325, 200, 100, 100, -2.5, 2, 0.9);
    g.strokePath(p1, PathStrokeType(5));
    p2.addPieSegment(325, 200, 100, 100, -2.5, 2, 0.9);
    g.setGradientFill(grade);
    g.fillPath(p2);
    
};

void Tab1::paintDialBackground(Graphics& g, int x, int y, int width, int height)
{
    Path p1;
    Path p2;
    Path p3;
    Path p4;
    g.setColour(Colours::grey);
    p4.addPieSegment(x, y, width, height, -2.5, 2, 0.9);
    g.strokePath(p4, PathStrokeType(5));
    g.setColour(Colours::green);
    p1.addPieSegment(x, y, width, height, -2.5, 1, 0.9);
    g.fillPath(p1);
    g.setColour(Colours::orange);
    p2.addPieSegment(x, y, width, height, 1, 1.5, 0.9);
    g.fillPath(p2);
    g.setColour(Colours::red);
    p3.addPieSegment(x, y, width, height, 1.5, 2, 0.9);
    g.fillPath(p3);
    
};


void Tab1::paint (Graphics& g)
{
    g.fillAll (Colours::ghostwhite);
    
    paintDialBackground(g, 25, 200, 100, 100);
    paintMixDialBackground(g);
    paintDialBackground(g, 625, 200, 100, 100);
    g.setColour(Colours::black);
    g.drawFittedText("input", 25, 275, 100, 100, Justification::centred, 1);
    g.drawFittedText("Thresh", 112, 275, 100, 100, Justification::centred, 1);
    g.drawFittedText("Ratio", 175, 275, 100, 100, Justification::centred, 1);
    g.drawFittedText("knee", 237, 275, 100, 100, Justification::centred, 1);
    g.drawFittedText("Mix", 325, 275, 100, 100, Justification::centred, 1);
    g.drawFittedText("Attack", 412, 275, 100, 100, Justification::centred,1 );
    g.drawFittedText("Release", 475, 275, 100, 100, Justification::centred, 1);
    g.drawFittedText("HPF", 537, 275, 100, 100, Justification::centred, 1);
    g.drawFittedText("make_up", 625, 275, 100, 100, Justification::centred, 1);
};

void Tab1::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
