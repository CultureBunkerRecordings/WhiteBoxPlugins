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
    FFAU::LevelMeterSource& getMeterSource()
    {
        return meterSource;
    }
    
    float T = -24.0;
    float R = 4.0;
    float attack = 100; //milli sec
    float release = 500;// milli secs
    float inputGain = 0.0;
    float outputGain = 0.0;
    float mix = 0.1;
    float knee = 0.0;

private:
    FFAU::LevelMeterSource meterSource; 
    float prevGainChange = 0.0;
    float Fs = 48000;
    

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorTarrAudioProcessor)
};
