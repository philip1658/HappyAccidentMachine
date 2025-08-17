#include "HamAudioProcessor.h"
#include "../../Domain/Engines/SequencerEngine.h"
#include "../../Domain/Engines/VoiceManager.h"
#include "../../Domain/Processors/MidiProcessor.h"

namespace HAM {
namespace Infrastructure {

HamAudioProcessor::HamAudioProcessor()
    : m_sampleRate(44100.0)
    , m_blockSize(512)
    , m_samplesProcessed(0)
{
    // Initialize domain components
    m_sequencer = std::make_unique<Domain::SequencerEngine>();
    m_voiceManager = std::make_unique<Domain::VoiceManager>();
    m_midiProcessor = std::make_unique<Domain::MidiProcessor>();
}

HamAudioProcessor::~HamAudioProcessor() = default;

void HamAudioProcessor::processBlock(float** audioBuffer, int numChannels, int numSamples) {
    // Clear audio buffer (HAM is a MIDI-only plugin for now)
    for (int channel = 0; channel < numChannels; ++channel) {
        for (int sample = 0; sample < numSamples; ++sample) {
            audioBuffer[channel][sample] = 0.0f;
        }
    }
    
    // Process timing and sequencer
    processTiming();
    
    // Update voice ages
    m_voiceManager->updateAges();
    
    m_samplesProcessed += numSamples;
}

void HamAudioProcessor::processMidi(void* midiMessages) {
    // In a real implementation, this would process JUCE MidiBuffer
    // For now, just a placeholder
    (void)midiMessages;
    
    generateMidiEvents();
}

void HamAudioProcessor::prepareToPlay(double sampleRate, int blockSize) {
    m_sampleRate = sampleRate;
    m_blockSize = blockSize;
    m_samplesProcessed = 0;
    
    // Reset sequencer
    m_sequencer->reset();
}

void HamAudioProcessor::releaseResources() {
    // Clean up any resources
    m_midiProcessor->clearEvents();
}

void HamAudioProcessor::getStateInformation(void* destData, int& destDataSize) {
    // In a real implementation, this would serialize the plugin state
    // For now, just return empty state
    (void)destData;
    destDataSize = 0;
}

void HamAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {
    // In a real implementation, this would deserialize the plugin state
    (void)data;
    (void)sizeInBytes;
}

void HamAudioProcessor::processTiming() {
    // Calculate if we need to advance the sequencer pulse
    // At 120 BPM, 24 PPQN = 48 pulses per second
    float bpm = m_sequencer->getTempo();
    double pulsesPerSecond = (bpm / 60.0) * Domain::SequencerEngine::PPQN;
    double samplesPerPulse = m_sampleRate / pulsesPerSecond;
    
    static double pulseAccumulator = 0.0;
    pulseAccumulator += m_blockSize;
    
    while (pulseAccumulator >= samplesPerPulse) {
        m_sequencer->processNextPulse();
        pulseAccumulator -= samplesPerPulse;
    }
}

void HamAudioProcessor::generateMidiEvents() {
    // Generate MIDI events from sequencer state
    // This would be more complex in a real implementation
    std::vector<Domain::MidiEvent> events;
    m_midiProcessor->processEvents(events, m_blockSize);
    
    // In a real implementation, these events would be added to JUCE's MidiBuffer
}

} // namespace Infrastructure
} // namespace HAM