#include "../JuceLibraryCode/JuceHeader.h"
#include "TransferFunction.h"

TransferFunction::TransferFunction(CompressorTarrAudioProcessor& p)
    : processor(p),
    xPos(0.0f)
{
    smoothOut.reset(60.0, 0.05);   // UI smoothing 50 ms
    startTimerHz(60);              // 60 FPS
}

TransferFunction::~TransferFunction() {}

void TransferFunction::paint(Graphics& g)
{
    const int w = getWidth();
    const int h = getHeight();

    if (w <= 2 || h <= 2)
        return;

    // ----------------------------------------
    // LAYOUT: reserve margin for Y-axis labels
    // ----------------------------------------
    const int labelMargin = 40;       // Left margin for labels
    const int graphX = labelMargin;   // Graph starts here
    const int graphW = w - labelMargin;

    const float topMargin = 10.0f;
    const float bottomMargin = 10.0f;
    const float graphHeight = h - (topMargin + bottomMargin);

    // Background
    g.fillAll(Colours::grey.withAlpha(0.1f));

    // ------------------------
    // Y-axis grid with dB labels
    // ------------------------
    constexpr float dBMarks[] = { -48, -36, -24, -18, -12, -6, 0 };
    constexpr int numMarks = sizeof(dBMarks) / sizeof(float);

    g.setColour(Colours::darkgrey.withAlpha(0.4f));
    g.setFont(12.0f);

    auto dBToY = [h, topMargin, bottomMargin, graphHeight](float dB)
        {
            // Map dBFS to pixel (top = 0 dB, bottom = -48 dB)
            float y = topMargin + jmap(dB, -48.0f, 0.0f, graphHeight, 0.0f);
            return std::clamp(y, topMargin, topMargin + graphHeight);
        };

    for (int i = 0; i < numMarks; ++i)
    {
        float db = dBMarks[i];
        float y = dBToY(db);

        // Horizontal grid line
        g.drawLine((float)graphX, y, (float)w, y, 1.0f);

        // Label
        g.drawText(String((int)db) + " dB",
            2,
            (int)y - 7,
            labelMargin - 4,
            14,
            Justification::centredRight);
    }

    // ------------------------
    // Fetch DSP parameters
    // ------------------------
    float safeThreshold = std::clamp(currentThreshold, -144.0f, 0.0f);
    float safeKnee = std::max(0.0001f, currentKnee);
    float safeRatio = std::max(0.01f, currentRatio);

    // ------------------------
    // Draw transfer curve
    // ------------------------
    Path curve;
    bool firstPoint = true;

    for (int i = 0; i < graphW; ++i)
    {
        float inLin = jmap<float>(i, 0.0f, (float)(graphW - 1), 0.0f, 1.0f);
        float in_dB = 20.0f * log10f(std::max(inLin, 1e-10f));
        in_dB = jmax(-144.0f, in_dB);

        float out_dB;

        if (2.0f * (in_dB - safeThreshold) < -safeKnee)
            out_dB = in_dB;
        else if (2.0f * fabs(in_dB - safeThreshold) <= safeKnee)
        {
            float delta = in_dB - safeThreshold + safeKnee * 0.5f;
            out_dB = in_dB + (1.0f / safeRatio - 1.0f) * (delta * delta) / (2.0f * safeKnee);
        }
        else
            out_dB = safeThreshold + (in_dB - safeThreshold) / safeRatio;

        // Map output dB to pixel
        float x = graphX + (float)i;
        float y = dBToY(out_dB);

        if (firstPoint)
        {
            curve.startNewSubPath(x, y);
            firstPoint = false;
        }
        else
            curve.lineTo(x, y);
    }

    g.setColour(Colours::black.withAlpha(0.35f));
    g.strokePath(curve, PathStrokeType(2));

    // ------------------------
    // Vertical grid
    // ------------------------
    Path grid;
    float gx = graphW / 8.0f;

    for (int j = 0; j <= 8; ++j)
    {
        float x = graphX + j * gx;
        grid.startNewSubPath(x, topMargin);
        grid.lineTo(x, topMargin + graphHeight);
    }

    g.setColour(Colours::darkgrey.withAlpha(0.3f));
    g.strokePath(grid, PathStrokeType(1));

    // ------------------------
    // Trailing output meter in dBFS
    // ------------------------
    float smoothed = smoothOut.getNextValue();
    smoothed = std::clamp(smoothed, 0.0f, 1.0f);
    float yOut = dBToY(20.0f * log10f(std::max(smoothed, 1e-10f)));

    int idx = static_cast<int>(xPos);
    float trailX = graphX + xPos;

    if (trailPoints.size() < (size_t)graphW)
        trailPoints.push_back({ trailX, yOut });
    else
        trailPoints[idx % graphW] = { trailX, yOut };

    Path trail;
    if (!trailPoints.empty())
    {
        trail.startNewSubPath(trailPoints[0]);
        for (size_t i = 1; i < trailPoints.size(); ++i)
        {
            float xP = std::clamp(trailPoints[i].x, (float)graphX, (float)w - 1.0f);
            float yP = std::clamp(trailPoints[i].y, topMargin, topMargin + graphHeight);
            trail.lineTo(xP, yP);
        }
    }

    g.setColour(Colours::red.withAlpha(0.35f));
    g.strokePath(trail, PathStrokeType(2));

    // ------------------------
    // Advance x-position
    // ------------------------
    xPos += 1.0f;
    if (xPos >= graphW)
        xPos = 0.0f;
}





void TransferFunction::timerCallback()
{
    // Update smoothed peak
    smoothOut.setTargetValue(processor.paintOut);

    // ===============================
    // READ RAW DSP PARAMETERS IN dB
    // (no normalization!)
    // ===============================
    currentThreshold = processor.parameters.getRawParameterValue("T")->load();       // dB
    currentKnee = processor.parameters.getRawParameterValue("knee")->load();    // dB
    currentRatio = processor.parameters.getRawParameterValue("R")->load();       // ratio

    repaint();
}

void TransferFunction::resized()
{
}
