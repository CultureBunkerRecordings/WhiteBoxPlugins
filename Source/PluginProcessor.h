#pragma once

#include <JuceHeader.h>

class CompressorTarrAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    CompressorTarrAudioProcessor();
    ~CompressorTarrAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    bool hasEditor() const override;
    juce::AudioProcessorEditor* createEditor() override;

    //==============================================================================
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    //==============================================================================
    // For visualization
    float paintOut = 0.0f;

    //==============================================================================
    void phaseSwitched();

    //==============================================================================
    // Sample rate & internal state
    double Fs = 44100.0;
    float prevGainChange = 0.0f;
    float phase = 1.0f;

    //==============================================================================
    // APVTS for parameters
    juce::AudioProcessorValueTreeState parameters;

    //==============================================================================
    // JUCE 6+ layout support
    bool isBusesLayoutSupported(const juce::AudioProcessor::BusesLayout& layouts) const override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CompressorTarrAudioProcessor)
};
