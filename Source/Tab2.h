/*
  ==============================================================================

    Tab2.h
    Created: 20 Dec 2019 3:10:30pm
    Author:  William Eden

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Tab2    : public Component
{
public:
    Tab2();
    ~Tab2();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Tab2)
};
