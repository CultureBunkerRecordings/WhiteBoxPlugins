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
TransferFunction::TransferFunction(CompressorTarrAudioProcessor& p): processor(p), xAxisThresh(0.5), yAxisThresh(0), yAxisRatio(2), xKnee(0.1), yKnee(0.1), xAxisInput(0), yAxisInput(0), count(0), xComp(0), yComp(0)
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
    
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    
    Path p;
    
    
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
    g.setColour (Colours::white);
    g.strokePath(p, PathStrokeType{ 1 });
    
}

void TransferFunction::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
