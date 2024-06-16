/*
 Cucu 14/06/2024
*/
#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
class AlgorithmicReverbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    AlgorithmicReverbAudioProcessorEditor (AlgorithmicReverbAudioProcessor&);
    ~AlgorithmicReverbAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    AlgorithmicReverbAudioProcessor& audioProcessor;

    juce::Slider(roomSizeSlider);
    juce::Slider(dampingSlider);
    juce::Slider(wetLevelSlider);
    juce::Slider(dryLevelSlider);
    juce::Slider(widthSlider);
    
    juce::Label(roomSizeLabel);
    juce::Label(dampingLabel);
    juce::Label(wetLevelLabel);
    juce::Label(dryLevelLabel);
    juce::Label(widthLabel);
    

    juce::TextButton(loadButton);
    juce::TextButton(playButton);

    std::unique_ptr<juce::FileChooser> fileChooser;

    void loadButtonClicked();
    void playButtonClicked();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlgorithmicReverbAudioProcessorEditor)
};
