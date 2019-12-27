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
TransferFunction::TransferFunction(CompressorTarrAudioProcessor& p): processor(p), yAxis(nullptr)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setBounds(200, 25, 400, 150); 
}

TransferFunction::~TransferFunction()
{
}


void TransferFunction::paint (Graphics& g)
{
    
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    
    
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    g.setColour (Colours::black);
    // draw an outline around the component

    g.setColour (Colours::white);
    g.drawLine(0, getHeight(), getWidth(), (int) -yAxis[count++]);
    g.setFont (14.0f);
    g.drawText ("TransferFunction", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
    if (count==100)
        count = 0;
}

void TransferFunction::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
