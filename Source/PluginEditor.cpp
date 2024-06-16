/*
Cucu 14/06/2024
*/
#include "PluginEditor.h"

AlgorithmicReverbAudioProcessorEditor::AlgorithmicReverbAudioProcessorEditor (AlgorithmicReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    const auto& reverbParams = audioProcessor.getReverbParameters();

    roomSizeSlider.setSliderStyle(juce::Slider::LinearVertical);
    roomSizeSlider.setRange(0.0, 1.0, 0.01);
    roomSizeSlider.setValue(reverbParams.roomSize);
    roomSizeSlider.onValueChange = [this] {
        auto params = audioProcessor.getReverbParameters();
        params.roomSize = roomSizeSlider.getValue();
        audioProcessor.setReverbParameters(params);
    };
    addAndMakeVisible(roomSizeSlider);

    dampingSlider.setSliderStyle(juce::Slider::LinearVertical);
    dampingSlider.setRange(0.0, 1.0, 0.01);
    dampingSlider.setValue(reverbParams.damping);
    dampingSlider.onValueChange = [this] {
        auto params = audioProcessor.getReverbParameters();
        params.damping = dampingSlider.getValue();
        audioProcessor.setReverbParameters(params);
    };
    addAndMakeVisible(dampingSlider);

    wetLevelSlider.setSliderStyle(juce::Slider::LinearVertical);
    wetLevelSlider.setRange(0.0, 1.0, 0.01);
    wetLevelSlider.setValue(reverbParams.wetLevel);
    wetLevelSlider.onValueChange = [this] {
        auto params = audioProcessor.getReverbParameters();
        params.wetLevel = wetLevelSlider.getValue();
        audioProcessor.setReverbParameters(params);
    };
    addAndMakeVisible(wetLevelSlider);

    dryLevelSlider.setSliderStyle(juce::Slider::LinearVertical);
    dryLevelSlider.setRange(0.0, 1.0, 0.01);
    dryLevelSlider.setValue(reverbParams.dryLevel);
    dryLevelSlider.onValueChange = [this] {
        auto params = audioProcessor.getReverbParameters();
        params.dryLevel = dryLevelSlider.getValue();
        audioProcessor.setReverbParameters(params);
    };
    addAndMakeVisible(dryLevelSlider);

    widthSlider.setSliderStyle(juce::Slider::LinearVertical);
    widthSlider.setRange(0.0, 1.0, 0.01);
    widthSlider.setValue(reverbParams.width);
    widthSlider.onValueChange = [this] {
        auto params = audioProcessor.getReverbParameters();
        params.width = widthSlider.getValue();
        audioProcessor.setReverbParameters(params);
    };
    addAndMakeVisible(widthSlider);

    roomSizeLabel.setText("size", juce::dontSendNotification); //room size
    addAndMakeVisible(roomSizeLabel);
    dampingLabel.setText("damping", juce::dontSendNotification); //damping
    addAndMakeVisible(dampingLabel);
    wetLevelLabel.setText("wet", juce::dontSendNotification); //wet level
    addAndMakeVisible(wetLevelLabel);
    dryLevelLabel.setText("dry", juce::dontSendNotification); //dry level
    addAndMakeVisible(dryLevelLabel);
    widthLabel.setText("width", juce::dontSendNotification);
    addAndMakeVisible(widthLabel);

    loadButton.setButtonText("load file");
    loadButton.onClick = [this] { loadButtonClicked(); };
    addAndMakeVisible(loadButton);

    playButton.setButtonText("play");
    playButton.onClick = [this] { playButtonClicked(); };
    addAndMakeVisible(playButton);

    setSize(500, 300);
}

AlgorithmicReverbAudioProcessorEditor::~AlgorithmicReverbAudioProcessorEditor()
{
}

void AlgorithmicReverbAudioProcessorEditor::loadButtonClicked()
{
    fileChooser = std::make_unique<juce::FileChooser>("Select a Wave file to play...", juce::File{}, "*.wav");
    auto chooserFlags = juce::FileBrowserComponent::canSelectFiles;
    fileChooser->launchAsync(chooserFlags, [this](const juce::FileChooser& chooser) {
        auto file = chooser.getResult();
        audioProcessor.loadFile(file);
    });
}

void AlgorithmicReverbAudioProcessorEditor::playButtonClicked()
{
    audioProcessor.startPlaying();
}

void AlgorithmicReverbAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void AlgorithmicReverbAudioProcessorEditor::resized()
{
    auto sliderWidth = 50;
    auto sliderHeight = getHeight() - 60;

    roomSizeSlider.setBounds(10, 20, sliderWidth, sliderHeight);
    dampingSlider.setBounds(70, 20, sliderWidth, sliderHeight);
    wetLevelSlider.setBounds(130, 20, sliderWidth, sliderHeight);
    dryLevelSlider.setBounds(190, 20, sliderWidth, sliderHeight);
    widthSlider.setBounds(250, 20, sliderWidth, sliderHeight);

    loadButton.setBounds(320, 20, 80, 30);
    playButton.setBounds(320, 60, 80, 30);

    roomSizeLabel.setBounds(10, getHeight() - 30, sliderWidth, 20);
    dampingLabel.setBounds(70, getHeight() - 30, sliderWidth, 20);
    wetLevelLabel.setBounds(130, getHeight() - 30, sliderWidth, 20);
    dryLevelLabel.setBounds(190, getHeight() - 30, sliderWidth, 20);
    widthLabel.setBounds(250, getHeight() - 30, sliderWidth, 20);
}
