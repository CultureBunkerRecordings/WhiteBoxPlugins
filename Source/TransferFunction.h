/*
    TransferFunction.h
    Updated for correct dB-domain drawing
    Author: William Eden
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class TransferFunction : public juce::Component,
    private juce::Timer
{
public:
    TransferFunction(CompressorTarrAudioProcessor& processorRef);
    ~TransferFunction() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:

    // ============================================================
    // Reference to the audio processor (for APVTS + paintOut)
    // ============================================================
    CompressorTarrAudioProcessor& processor;

    // ============================================================
    // LIVE DSP PARAMETERS (in dB / ratio)
    // Set every timer tick — never normalized.
    // ============================================================
    float currentThreshold = -20.0f;   // dB
    float currentKnee = 6.0f;    // dB
    float currentRatio = 4.0f;    // ratio

    // ============================================================
    // OUTPUT VISUALIZATION
    // ============================================================
    juce::SmoothedValue<float> smoothOut;        // smoothed paintOut (0..1)
    std::vector<juce::Point<float>> trailPoints; // ring buffer of output points
    float xPos = 0.0f;                            // animation position

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TransferFunction)
};
