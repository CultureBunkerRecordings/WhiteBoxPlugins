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
Tab1::Tab1()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

Tab1::~Tab1()
{
}

void Tab1::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("Tab1", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void Tab1::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
