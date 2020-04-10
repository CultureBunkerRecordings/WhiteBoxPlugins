/*
  ==============================================================================

    TransferFunction.cpp
    Created: 20 Dec 2019 10:12:18am
    Author:  William Eden

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TransferFunction.h"
//==============================================================================
TransferFunction::TransferFunction(CompressorTarrAudioProcessor& p): processor(p), xComp(0), yComp(0), xAxisThresh(1), yAxisRatio(1), xKnee(0), xAxisInput(0), paintOutX(0), paintOutY(0)
{
     //In your constructor, you should add any child components, and
    //initialise any special settings that your component needs.
    setBounds(200, 25, 400, 150);
    
}

TransferFunction::~TransferFunction()
{
}

void TransferFunction::paint(Graphics& g)
{
    
    
    
    //*******************************************************************************
    //background colour
    g.fillAll (juce::Colours::grey);
    
    //*******************************************************************************
    //path to draw transfer function from
    Path p;
    
    //loop for drawing tranfer function, transfer function taken from PluginProcessor.cpp
    for (int i = 0; i < getWidth(); ++i){
        
        float insample = jmap<float>(i, 0.0, getWidth(), 0.0, 1.0);
        float yOut = 0.0f;
        
        if (2*(insample - xAxisThresh) < -xKnee)
        {
            //no comp
            yOut = insample;

        }
        else if (2* abs(insample - xAxisThresh) <= xKnee)
        {
            //yes comp
            yOut = insample+(1/yAxisRatio - 1)* std::pow(insample - xAxisThresh + xKnee/2, 2)/(2*xKnee);
        }
        else if (2 * (insample - xAxisThresh) > xKnee){
            yOut = xAxisThresh + (insample - xAxisThresh)/yAxisRatio;
        }
        float ycor = jmap<float>(yOut, 0.0f, 1.0f, getHeight(), 0.0);
        p.lineTo(i, ycor);
    }
    
    //*******************************************************************************
    //path to draw grid from
    Path p2;
    Path p3;
    
    float gridY = 18.75; //height/8
    float gridX = 50;//width/8
    
    //loop for drawing graph
    for(int j = 0; j<8; ++j){
        p2.startNewSubPath(0, gridY * j);
        p2.lineTo(getWidth(), gridY * j);
        for(int x = 0; x<8; ++x){
            p2.startNewSubPath(gridX * x, 0);
            p2.lineTo(gridX * x, getHeight());
        }
    };
    
    
    
    //*******************************************************************************
    //set colour and fill paths
    
    g.setColour(Colours::darkgrey);
    g.strokePath(p2, PathStrokeType(1));
    
    g.setColour (Colours::white);
    g.strokePath(p, PathStrokeType(2));
    
    for (int i = 0; i<getHeight(); i++){
        p3.startNewSubPath(0, getHeight());
        paintOutY = jmap<float>(processor.paintOut, getHeight(), 0);
        paintOutX = jmap<float>(processor.paintOut, 0, getWidth());
        
        p3.lineTo(paintOutX, paintOutY);
        g.setColour(Colours::red);
        g.strokePath(p3, PathStrokeType(3));
        
    };
    
}

void TransferFunction::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}



