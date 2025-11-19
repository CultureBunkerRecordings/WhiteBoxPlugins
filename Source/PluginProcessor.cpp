/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorTarrAudioProcessor::CompressorTarrAudioProcessor()
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
    parameters(*this, nullptr, "PARAMETERS",
        {
            std::make_unique<juce::AudioParameterFloat>("T", "Threshold", -64.0f, 0.0f, 0.0f),
            std::make_unique<juce::AudioParameterFloat>("R", "Ratio", 1.0f, 10.0f, 1.0f),
            std::make_unique<juce::AudioParameterFloat>("attack", "Attack", 0.0f, 1500.0f, 500.0f),
            std::make_unique<juce::AudioParameterFloat>("release", "Release", 0.0f, 3000.0f, 500.0f),
            std::make_unique<juce::AudioParameterFloat>("inputGain", "Input Gain", -48.0f, 12.0f, 0.0f),
            std::make_unique<juce::AudioParameterFloat>("outputGain", "Output Gain", -48.0f, 12.0f, 0.0f),
            std::make_unique<juce::AudioParameterFloat>("mix", "Mix", 0.0f, 100.0f, 0.0f),
            std::make_unique<juce::AudioParameterFloat>("knee", "Knee", 0.0f, 10.0f, 0.0f),
            std::make_unique<juce::AudioParameterFloat>("hpf", "Hpf", 0.0f, 10.0f, 0.0f)
        })
{
}


CompressorTarrAudioProcessor::~CompressorTarrAudioProcessor()
{
}

//==============================================================================
const String CompressorTarrAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CompressorTarrAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CompressorTarrAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CompressorTarrAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CompressorTarrAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CompressorTarrAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CompressorTarrAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CompressorTarrAudioProcessor::setCurrentProgram (int index)
{
}

const String CompressorTarrAudioProcessor::getProgramName (int index)
{
    return {};
}

void CompressorTarrAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void CompressorTarrAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    Fs = sampleRate;
    
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void CompressorTarrAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CompressorTarrAudioProcessor::isBusesLayoutSupported(const juce::AudioProcessor::BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
#else
    // Only mono or stereo output is supported
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // Input must match output (unless synth)
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif



void CompressorTarrAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto numSamples = buffer.getNumSamples();

    // Load parameters safely
    float threshold = parameters.getRawParameterValue("T")->load();
    float ratio = std::max(0.01f, parameters.getRawParameterValue("R")->load()); // prevent divide by zero
    float atk = std::max(0.1f, parameters.getRawParameterValue("attack")->load()); // ms
    float rel = std::max(0.1f, parameters.getRawParameterValue("release")->load()); // ms
    float inGain = parameters.getRawParameterValue("inputGain")->load();
    float outGain = parameters.getRawParameterValue("outputGain")->load();
    float mixVal = jlimit(0.0f, 100.0f, parameters.getRawParameterValue("mix")->load());
    float kneeVal = std::max(0.0001f, parameters.getRawParameterValue("knee")->load()); // prevent divide by zero
    float hpf = parameters.getRawParameterValue("hpf")->load();

    // Clear extra output channels
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, numSamples);

    // Convert attack/release to smoothing coefficients
    float alphaA = expf(-logf(9.0f) / (Fs * atk * 0.001f)); // ms -> seconds
    float alphaR = expf(-logf(9.0f) / (Fs * rel * 0.001f));

    float peakOutput = 0.0f;

    for (int sample = 0; sample < numSamples; ++sample)
    {
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            // Apply input gain
            float linIn = powf(10.0f, inGain / 20.0f);
            float x = buffer.getWritePointer(channel)[sample] * linIn;

            // Convert to dB safely
            float x_dB = 20.0f * log10f(std::max(fabs(x), 1e-10f));
            x_dB = jmax(-144.0f, x_dB);

            // Compute compressor output dB
            float xSC = x_dB;

            if (2.0f * (x_dB - threshold) < -kneeVal)
            {
                xSC = x_dB;
            }
            else if (2.0f * fabs(x_dB - threshold) <= kneeVal)
            {
                float delta = x_dB - threshold + kneeVal * 0.5f;
                xSC = x_dB + (1.0f / ratio - 1.0f) * (delta * delta) / (2.0f * kneeVal);
            }
            else
            {
                xSC = threshold + (x_dB - threshold) / ratio;
            }

            // Smooth gain change
            float gainChange = xSC - x_dB;
            float gainChangeSmooth = (gainChange < prevGainChange)
                ? (1.0f - alphaA) * gainChange + alphaA * prevGainChange
                : (1.0f - alphaR) * gainChange + alphaR * prevGainChange;

            prevGainChange = gainChangeSmooth;

            // Convert back to linear
            float gLin = powf(10.0f, gainChangeSmooth / 20.0f);
            float linOut = powf(10.0f, outGain / 20.0f);

            float output = gLin * x * linOut;

            // Mix dry/wet safely
            float mixer = jlimit(0.0f, 1.0f, mixVal / 100.0f);
            buffer.getWritePointer(channel)[sample] = mixer * output + (1.0f - mixer) * x;

            // Track peak for visualization
            peakOutput = jmax(peakOutput, fabs(output));
        }
    }

    // Clamp for TransferFunction visualization
    paintOut = jlimit(0.0f, 1.0f, peakOutput);
}


//==============================================================================
bool CompressorTarrAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* CompressorTarrAudioProcessor::createEditor()
{
    return new CompressorTarrAudioProcessorEditor (*this);
}

//==============================================================================
void CompressorTarrAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void CompressorTarrAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr)
    {
        parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
    }
    
}

void CompressorTarrAudioProcessor::phaseSwitched()
{
    phase *= -1;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CompressorTarrAudioProcessor();
}
