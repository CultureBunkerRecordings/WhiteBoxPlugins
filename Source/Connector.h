/*
  ==============================================================================

    Connector.h
    Created: 26 Dec 2019 5:17:24pm
    Author:  William Eden

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "TransferFunction.h"
#include "Tab1.h"

class Connector : public Component
{
public:
    Connector(CompressorTarrAudioProcessor& p): processor(p), Tf(p), T(p){
        Tf.get = [this](){return T.getAxisSlider();};
        Tf.startTimerHz(60);
    };
    Tab1 T;
    TransferFunction Tf;
    CompressorTarrAudioProcessor& processor;
};

