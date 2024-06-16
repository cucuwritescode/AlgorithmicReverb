/*
 Cucu 14/06/2024
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>

void AlgorithmicReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    std::cout << "prepareToPlay called" << std::endl;
    std::cout << "Sample Rate: " << sampleRate << ", Samples Per Block: " << samplesPerBlock << std::endl;

    reverb.setSampleRate(sampleRate);
    reverb.setParameters(reverbParams);
    transportSource.prepareToPlay(samplesPerBlock, sampleRate);
}

void AlgorithmicReverbAudioProcessor::releaseResources()
{
    std::cout << "releaseResources called" << std::endl;
    transportSource.releaseResources();
}

void AlgorithmicReverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    std::cout << "Total input channels: " << totalNumInputChannels << std::endl;
    std::cout << "Total output channels: " << totalNumOutputChannels << std::endl;

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (auto channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        std::cout << "Processing channel: " << channel << ", Num samples: " << buffer.getNumSamples() << std::endl;
    }

    auto* leftChannel = buffer.getWritePointer(0);
    auto* rightChannel = buffer.getWritePointer(1);
    reverb.processStereo(leftChannel, rightChannel, buffer.getNumSamples());

    transportSource.getNextAudioBlock(juce::AudioSourceChannelInfo(buffer));
}

juce::AudioProcessorEditor* AlgorithmicReverbAudioProcessor::createEditor()
{
    return new AlgorithmicReverbAudioProcessorEditor (*this);
}

bool AlgorithmicReverbAudioProcessor::hasEditor() const
{
    return true;
}

const juce::String AlgorithmicReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AlgorithmicReverbAudioProcessor::acceptsMidi() const
{
    return false;
}

bool AlgorithmicReverbAudioProcessor::producesMidi() const
{
    return false;
}

bool AlgorithmicReverbAudioProcessor::isMidiEffect() const
{
    return false;
}

double AlgorithmicReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AlgorithmicReverbAudioProcessor::getNumPrograms()
{
    return 1;
}

int AlgorithmicReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AlgorithmicReverbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AlgorithmicReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void AlgorithmicReverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void AlgorithmicReverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

void AlgorithmicReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

void AlgorithmicReverbAudioProcessor::loadFile(const juce::File& file)
{
    std::cout << "loadFile called with file: " << file.getFullPathName() << std::endl;
    auto* reader = formatManager.createReaderFor(file);

    if (reader != nullptr)
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset (newSource.release());
    }
}

void AlgorithmicReverbAudioProcessor::startPlaying()
{
    std::cout << "startPlaying called" << std::endl;
    transportSource.start();
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AlgorithmicReverbAudioProcessor();
}
