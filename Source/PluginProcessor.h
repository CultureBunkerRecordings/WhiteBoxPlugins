/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
//==============================================================================
/**
*/
class CompressorTarrAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    CompressorTarrAudioProcessor();
    ~CompressorTarrAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void phaseSwitched();

    
    AudioParameterFloat* T;
    AudioParameterFloat* R;
    AudioParameterFloat* attack; //milli sec
    AudioParameterFloat* release;// milli secs
    AudioParameterFloat* inputGain;
    AudioParameterFloat* outputGain;
    AudioParameterFloat* mix;
    AudioParameterFloat* knee;
    
    int phase = 1;
    float paintOut = 0.0f;

    
private:
    float prevGainChange = 0.0;
    float Fs = 48000;
    

    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorTarrAudioProcessor)
};
