/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorTarrAudioProcessor::CompressorTarrAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(T = new AudioParameterFloat("T", "Threshold", -64.0f, 0.0f, 0.0f));
    addParameter(R = new AudioParameterFloat("R", "Ratio", 1.0f, 10.0f, 1.0f));
    addParameter(attack = new AudioParameterFloat("attack", "Attack", 0.0f, 1500.0f, 500.0f));
    addParameter(release = new AudioParameterFloat("release", "Release", 0.0f, 3000.0f, 500.0f));
    addParameter(inputGain = new AudioParameterFloat("inputGain", "Input Gain", -48.0f, 12.0f, 0.0f));
    addParameter(outputGain = new AudioParameterFloat("outputGain", "Output Gain", -48.0, 12.0f, 0.0f));
    addParameter(mix = new AudioParameterFloat("mix", "Mix", 0.0f, 100.0f, 0.0f));
    addParameter(knee = new AudioParameterFloat("knee", "Knee", 0.0f, 10.0f, 0.0f));
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
bool CompressorTarrAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CompressorTarrAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    float alphaA = exp(-logf(9.0)/(Fs * (*attack) * 0.0001));
    float alphaR = exp(-logf(9.0)/(Fs * (*release) * 0.0001));
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int sample = 0; sample<buffer.getNumSamples();++sample)
    {
    
        for (int channel = 0; channel < totalNumInputChannels; ++channel){
            
            float linIn = powf(10.0f, (*inputGain)/20.0f);
            
            float x = buffer.getWritePointer (channel)[sample] * linIn;
            
//            meterSource.measureBlock(buffer);
            
            //this is where compressor goes
            float x_Pos = fabs(x);
            float x_dB = 20*log10(x_Pos);
            
            if (x_dB < -144.0f)
            {
                x_dB = -144.0f;
                
            }
            // x_dB = jmax(-144.0f, x_dB);      juce way
            
            float xSC = 0;
            
            if (2*(x_dB - *T) < -*knee)
            {
                //no comp
                xSC = x_dB;
            }
            else if (2* abs(x_dB - *T)<= *knee)
            {
                //yes comp
                xSC = x_dB+(1/(*R) - 1)*std::pow(x_dB - (*T)+(*knee)/2, 2)/(2 * (*knee));
            }
            else{
                xSC = *T+(x_dB - *T)/(*R);
            }
                //compare
            float gainChange = xSC - x_dB;
            float gainChangeSmooth;
                //smooth
            if (gainChange < prevGainChange){
                    //attack
                    gainChangeSmooth = (1- alphaA) * gainChange + alphaA * prevGainChange;

                }
            else{
                    //release
                    gainChangeSmooth = (1- alphaR) * gainChange + alphaR * prevGainChange;

                
                }
            
            float gLin = powf(10.0f, gainChangeSmooth/20.0f);
            
            prevGainChange = gainChangeSmooth;
            
            float linOut = powf(10.0f, (*outputGain)/20.0f);
            
            float output = (gLin * x) * linOut;
            
            float mixer = (*mix)/100;
            
            buffer.getWritePointer(channel)[sample] = phase * mixer*output + (1-mixer)*x;
            
            if(sample % 100 == 0)
            {
                paintOut = output;
            }
            
        }// ..do something to the data...
    }
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
    
    std::unique_ptr<XmlElement> xml(new XmlElement("Params"));
    xml->setAttribute("T", static_cast<double>(*T));
    xml->setAttribute("R", static_cast<double>(*R));
    xml->setAttribute("attack", static_cast<double>(*attack));
    xml->setAttribute("release", static_cast<double>(*release));
    xml->setAttribute("inputGain", static_cast<double>(*inputGain));
    xml->setAttribute("outputGain", static_cast<double>(*outputGain));
    xml->setAttribute("mix", static_cast<double>(*mix));
    xml->setAttribute("knee", static_cast<double>(*knee));
    copyXmlToBinary(*xml, destData);
}

void CompressorTarrAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if(xmlState != nullptr){
        if(xmlState->hasTagName("Params")){
            *T = xmlState->getDoubleAttribute("T", 0.0);
            *R = xmlState->getDoubleAttribute("R", 1.0);
            *attack = xmlState->getDoubleAttribute("attack", 0.0);
            *release = xmlState->getDoubleAttribute("release", 0.0);
            *inputGain = xmlState->getDoubleAttribute("inputGain", 0.0);
            *outputGain = xmlState->getDoubleAttribute("outputGain", 0.0);
            *mix = xmlState->getDoubleAttribute("mix", 0.0);
            *knee = xmlState->getDoubleAttribute("knee", 0.0);
        }
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
