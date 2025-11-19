/*
  ==============================================================================

    Tab1.cpp
    Created: 18 Dec 2019 12:48:13pm
    Author:  William Eden

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Tab1.h"

Tab1::Tab1(CompressorTarrAudioProcessor& p)
    : processor(p), trans(p), isClicked(false)
{
    setLookAndFeel(&tabLookAndFeel);

    startTimerHz(60); // repaint timer

    // -----------------------
    // Setup sliders & attachments
    // -----------------------
    // Input Gain
    addAndMakeVisible(inputSlider);
    inputSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    inputSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    inputSlider.setRange(-48.0f, 12.0f);
    inputAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "inputGain", inputSlider);
    inputSlider.setColour(Slider::textBoxTextColourId, Colours::black);

    // Output Gain
    addAndMakeVisible(outputSlider);
    outputSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    outputSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    outputSlider.setRange(-48.0f, 12.0f);
    outputAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "outputGain", outputSlider);
    outputSlider.setColour(Slider::textBoxTextColourId, Colours::black);

    // Mix
    addAndMakeVisible(mixSlider);
    mixSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    mixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    mixSlider.setRange(0.0f, 100.0f);
    mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "mix", mixSlider);
    mixSlider.setColour(Slider::textBoxTextColourId, Colours::black);

    // Threshold
    addAndMakeVisible(threshSlider);
    threshSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    threshSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    threshSlider.setRange(-64.0f, 0.0f);
    threshAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "T", threshSlider);
    threshSlider.setColour(Slider::textBoxTextColourId, Colours::black);

    // Ratio
    addAndMakeVisible(ratioSlider);
    ratioSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    ratioSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    ratioSlider.setRange(1.0f, 10.0f);
    ratioAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "R", ratioSlider);
    ratioSlider.setColour(Slider::textBoxTextColourId, Colours::black);

    // Knee
    addAndMakeVisible(kneeSlider);
    kneeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    kneeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    kneeSlider.setRange(0.0f, 10.0f);
    kneeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "knee", kneeSlider);
    kneeSlider.setColour(Slider::textBoxTextColourId, Colours::black);

    // Attack
    addAndMakeVisible(attackSlider);
    attackSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    attackSlider.setRange(0.0f, 1500.0f);
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "attack", attackSlider);
    attackSlider.setColour(Slider::textBoxTextColourId, Colours::black);

    // Release
    addAndMakeVisible(releaseSlider);
    releaseSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    releaseSlider.setRange(0.0f, 3000.0f);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "release", releaseSlider);
    releaseSlider.setColour(Slider::textBoxTextColourId, Colours::black);

    // HPF
    addAndMakeVisible(hpfSlider);
    hpfSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    hpfSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
    hpfSlider.setRange(0.0f, 500.0f);
    hpfAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "hpf", hpfSlider);
    hpfSlider.setColour(Slider::textBoxTextColourId, Colours::black);

    // -----------------------
    // Make TransferFunction visible
    // -----------------------
    addAndMakeVisible(&trans);

    help.setButtonText("White Box");
    addAndMakeVisible(help);
    help.addListener(this);
    help.setColour(ToggleButton::tickColourId, Colours::black);
    help.setColour(ToggleButton::textColourId, Colours::black);

    phaseInvert.setButtonText("Phase Invert");
    addAndMakeVisible(phaseInvert);
    phaseInvert.addListener(this);
    phaseInvert.setColour(ToggleButton::tickColourId, Colours::black);
    phaseInvert.setColour(ToggleButton::textColourId, Colours::black);

    // -----------------------
    // Bubble message components
    // -----------------------
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
    setLookAndFeel(nullptr);
};

//*******************************************************************************
void Tab1::timerCallback()
{
    //*******************************************************************************
    // show BubbleMessage if component is clicked
    
    if(isClicked == true){
    
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
    }
    //*******************************************************************************
    //repaint canvas at each iteration
    
    trans.repaint();
};

void Tab1::sliderValueChanged (Slider* slider) // [1]
{
    //*******************************************************************************
    //nothing happening yet
};

//*******************************************************************************
//nothing happening yet
void Tab1::buttonClicked (Button* button) // [2]
{
    if(button == &help && isClicked == false){
        isClicked = true;
    }
    else if (button == &help && isClicked == true){
        isClicked = false;
    }
    
    if(button == &phaseInvert)
    {
        processor.phaseSwitched();
    }
};

//*******************************************************************************
// code for drawing other dial backgrounds

void Tab1::paintDialBackground(Graphics& g,
    int x, int y,
    int width, int height)
{
    constexpr float start = -2.5f;   // 7 o'clock
    constexpr float end = 2.0f;      // 4 o'clock
    constexpr float thickness = 0.85f;

    // Outer grey stroke
    Path arcStroke;
    arcStroke.addPieSegment((float)x, (float)y,
        (float)width, (float)height,
        start, end, thickness);
    g.setColour(Colours::black);
    g.strokePath(arcStroke, PathStrokeType(5.0f));

    // ------------------------
    // White → Dark Grey gradient fill
    // ------------------------
    float cx = x + width * 0.5f;
    float cy = y + height * 0.5f;

    // Create a simple linear gradient from left to right across the arc bounds
    ColourGradient grad(Colours::white, cx - width * 0.5f, cy,
        Colours::darkgrey, cx + width * 0.5f, cy,
        false);

    // Define the pie segment (arc) to fill
    Path arcFill;
    arcFill.addPieSegment((float)x, (float)y,
        (float)width, (float)height,
        start, end, thickness);

    // Apply gradient and fill the arc
    g.setGradientFill(grad);
    g.fillPath(arcFill);
}





void Tab1::paint (Graphics& g)
{
    g.fillAll (Colours::ghostwhite);
    int sliderSize = 100;

    // Only draw backgrounds for the three large knobs:
    paintDialBackground(g, 25, 200, sliderSize, sliderSize);   // Input
    paintDialBackground(g, 322, 200, sliderSize, sliderSize);// Mix (uses fixed 325,200)
    paintDialBackground(g, 625, 200, sliderSize, sliderSize);  // Output

    
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
    int sliderSize = 100;

    inputSlider.setBounds(25, 200, sliderSize, sliderSize);
    threshSlider.setBounds(112, 200, sliderSize, sliderSize);
    ratioSlider.setBounds(175, 200, sliderSize, sliderSize);
    kneeSlider.setBounds(237, 200, sliderSize, sliderSize);
    mixSlider.setBounds(325, 200, sliderSize, sliderSize);
    attackSlider.setBounds(412, 200, sliderSize, sliderSize);
    releaseSlider.setBounds(475, 200, sliderSize, sliderSize);
    hpfSlider.setBounds(537, 200, sliderSize, sliderSize);
    outputSlider.setBounds(625, 200, sliderSize, sliderSize);

    // --- Buttons stacked on right ---
    int buttonWidth = 100;
    int buttonHeight = 25;
    int marginRight = 25;
    int spacing = 10; // space between buttons

    int startX = getWidth() - marginRight - buttonWidth;
    int startY = 50;

    help.setBounds(startX, startY + (buttonHeight + spacing), buttonWidth, buttonHeight);
    phaseInvert.setBounds(startX, startY + 2 * (buttonHeight + spacing), buttonWidth, buttonHeight);


    int tfWidth = 400;
    int tfHeight = 150;

    int tfX = (getWidth() - tfWidth) / 2;   // center horizontally
    int tfY = (getHeight() - tfHeight) / 2;  // center vertically

    tfY -= 75;

    trans.setBounds(tfX, tfY, tfWidth, tfHeight);
}
