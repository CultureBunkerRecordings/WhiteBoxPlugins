#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class OtherLookAndFeel : public LookAndFeel_V4
{
public:
    OtherLookAndFeel() {}

    // --- Rotary slider ---
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos,
        const float rotaryStartAngle,
        const float rotaryEndAngle,
        Slider& slider) override
    {
        // Load dial image
        Image dialImage = ImageCache::getFromMemory(BinaryData::knobInner_png,
            BinaryData::knobInner_pngSize);

        if (!dialImage.isValid())
        {
            g.setColour(Colours::red);
            g.fillEllipse((float)x, (float)y, (float)width, (float)height);
            return;
        }

        const int size = jmin(width, height);
        const float margin = size * 0.05f;
        const int drawSize = (int)(size - 2.0f * margin);

        Image scaled = dialImage.rescaled(drawSize, drawSize);

        float cx = x + width * 0.5f;
        float cy = y + height * 0.5f;

        // adjust vertical alignment
        cy += 6.0f;

        // PNG is pointing southwest (≈ 225°)
        constexpr float pngOffset = 3.92699f;

        float angle = rotaryStartAngle +
            sliderPos * (rotaryEndAngle - rotaryStartAngle) -
            pngOffset;

        AffineTransform t = AffineTransform::rotation(angle,
            scaled.getWidth() * 0.5f,
            scaled.getHeight() * 0.5f)
            .translated(cx - scaled.getWidth() * 0.5f,
                cy - scaled.getHeight() * 0.5f);

        g.drawImageTransformed(scaled, t);
    }

    // --- Toggle buttons (checkbox style) ---
    void drawToggleButton(Graphics& g, ToggleButton& button,
        bool shouldDrawButtonAsHighlighted,
        bool shouldDrawButtonAsDown) override
    {
        const int boxSize = 16;
        const int gap = 6;

        const int boxX = 0;
        const int boxY = (button.getHeight() - boxSize) / 2;

        g.setColour(Colours::grey);
        g.fillRect(boxX, boxY, boxSize, boxSize);

        if (button.getToggleState())
        {
            g.setColour(Colours::white);
            g.drawLine(boxX + 3, boxY + boxSize / 2,
                boxX + boxSize / 2, boxY + boxSize - 3, 2.0f);

            g.drawLine(boxX + boxSize / 2, boxY + boxSize - 3,
                boxX + boxSize - 3, boxY + 3, 2.0f);
        }

        g.setColour(Colours::black);
        g.setFont(14.0f);

        const int textX = boxX + boxSize + gap;
        g.drawText(button.getButtonText(),
            textX, 0,
            button.getWidth() - textX, button.getHeight(),
            Justification::centredLeft, true);
    }

    // --- Button background ---
    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
        bool isMouseOverButton, bool isButtonDown) override
    {
        setColour(TextButton::buttonColourId, Colours::lightgrey);

        auto area = button.getLocalBounds();
        const int edge = 4;

        area.removeFromLeft(edge);
        area.removeFromTop(edge);

        g.setColour(Colours::darkgrey.withAlpha(0.5f));
        g.fillRect(area);

        int offset = isButtonDown ? -edge / 2 : -edge;
        area.translate(offset, offset);

        g.setColour(backgroundColour);
        g.fillRect(area);
    }

    // --- button text ---
    void drawButtonText(Graphics& g, TextButton& button,
        bool isMouseOverButton, bool isButtonDown) override
    {
        auto font = getTextButtonFont(button, button.getHeight());
        g.setFont(font);

        g.setColour(Colours::black.withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f));

        const int yIndent = jmin(4, button.proportionOfHeight(0.3f));
        const int cornerSize = jmin(button.getHeight(), button.getWidth()) / 2;
        const int fontHeight = roundToInt(font.getHeight() * 0.6f);

        const int leftIndent = jmin(fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
        const int rightIndent = jmin(fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));

        const int textWidth = button.getWidth() - leftIndent - rightIndent;

        const int edge = 4;
        const int offset = isButtonDown ? edge / 2 : 0;

        if (textWidth > 0)
        {
            g.drawFittedText(button.getButtonText(),
                leftIndent + offset,
                yIndent + offset,
                textWidth,
                button.getHeight() - yIndent * 2 - edge,
                Justification::centred,
                2);
        }
    }
};
