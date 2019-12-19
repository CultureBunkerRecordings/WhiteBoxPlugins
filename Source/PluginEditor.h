/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "dial.h"
//==============================================================================
/**
*/


class OtherLookAndFeel : public LookAndFeel_V4
{
public:
    OtherLookAndFeel(){
    }
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        AffineTransform rotator;
        
        //load image
        Image dialStart = ImageCache::getFromMemory(dial::knobInner_png, dial::knobInner_pngSize);
        
        //rescale image to fit
        const Image reDialStart = dialStart.rescaled(width, width);
        
        //rotate image
        g.drawImageTransformed(reDialStart, rotator.rotation(sliderPos*rotaryEndAngle/2, reDialStart.getWidth()/2, reDialStart.getHeight()/2));
    };
    
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override
    {
        setColour(TextButton::buttonColourId, juce::Colours::lightgrey);
       
        auto buttonArea = button.getLocalBounds();
        auto edge = 4;
        
        buttonArea.removeFromLeft (edge);
        buttonArea.removeFromTop (edge);
        
        // shadow
        g.setColour (Colours::darkgrey.withAlpha (0.5f));
        g.fillRect (buttonArea);

        auto offset = isButtonDown ? -edge / 2 : -edge;
        buttonArea.translate (offset, offset);
        
        g.setColour (backgroundColour);
        g.fillRect (buttonArea);
    };
    
    void drawButtonText (Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) override
    {

        auto font = getTextButtonFont (button, button.getHeight());
        g.setFont (font);
        g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                        : TextButton::textColourOffId)
                     .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));
        
        
        auto yIndent = jmin (4, button.proportionOfHeight (0.3f));
        auto cornerSize = jmin (button.getHeight(), button.getWidth()) / 2;
        
        auto fontHeight = roundToInt (font.getHeight() * 0.6f);
        auto leftIndent  = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft()  ? 4 : 2));
        auto rightIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
        auto textWidth = button.getWidth() - leftIndent - rightIndent;
        
        auto edge = 4;
        auto offset = isButtonDown ? edge / 2 : 0;
        
        if (textWidth > 0)
            g.drawFittedText (button.getButtonText(),
                              leftIndent + offset, yIndent + offset, textWidth, button.getHeight() - yIndent * 2 - edge,
                              Justification::centred, 2);
    };
    
    
};


class CompressorTarrAudioProcessorEditor  : public AudioProcessorEditor,
                                                   Slider::Listener,
                                                   Button::Listener
{
public:
    CompressorTarrAudioProcessorEditor (CompressorTarrAudioProcessor&);
    ~CompressorTarrAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void paintDialBackground(Graphics& g, int x, int y, int width, int height);
    void paintMixDialBackground(Graphics& g);
    void resized() override;
    void sliderValueChanged(Slider* slider) override;
    void buttonClicked (Button* button) override; // [2]
    
private:
    OtherLookAndFeel otherLookAndFeel;
    ScopedPointer<FFAU::LevelMeterLookAndFeel> lnf;
    ScopedPointer<FFAU::LevelMeter> meter;
    
    Slider inputSlider;
    Slider outputSlider;
    Slider mixSlider;
    Slider threshSlider;
    Slider ratioSlider;
    Slider kneeSlider;
    Slider attackSlider;
    Slider releaseSlider;
    Slider hpfSlider;
    TextButton whiteBox;
    TextButton help;
    
    //currently implementing overriding Component classes for tabs
//    TabbedComponent tabs;
//    Component tab;
//    Component tab2;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CompressorTarrAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorTarrAudioProcessorEditor)
};
