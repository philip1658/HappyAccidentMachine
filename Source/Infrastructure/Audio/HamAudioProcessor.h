#pragma once

// HamAudioProcessor.h - JUCE AudioProcessor implementation
// Bridge between JUCE and HAM's domain layer

#include <memory>

// Forward declarations to avoid JUCE dependency in header
namespace HAM {
namespace Domain {
    class SequencerEngine;
    class VoiceManager;
    class MidiProcessor;
}
}

namespace HAM {
namespace Infrastructure {

/**
 * JUCE AudioProcessor implementation for HAM
 * Bridges JUCE framework with HAM's domain layer
 */
class HamAudioProcessor {
public:
    HamAudioProcessor();
    virtual ~HamAudioProcessor();
    
    // Audio processing
    void processBlock(float** audioBuffer, int numChannels, int numSamples);
    void processMidi(void* midiMessages); // Generic MIDI processing
    
    // Configuration
    void prepareToPlay(double sampleRate, int blockSize);
    void releaseResources();
    
    // Plugin state
    void getStateInformation(void* destData, int& destDataSize);
    void setStateInformation(const void* data, int sizeInBytes);
    
    // Sequencer access
    Domain::SequencerEngine& getSequencer() { return *m_sequencer; }
    Domain::VoiceManager& getVoiceManager() { return *m_voiceManager; }

private:
    std::unique_ptr<Domain::SequencerEngine> m_sequencer;
    std::unique_ptr<Domain::VoiceManager> m_voiceManager;
    std::unique_ptr<Domain::MidiProcessor> m_midiProcessor;
    
    double m_sampleRate;
    int m_blockSize;
    int m_samplesProcessed;
    
    void processTiming();
    void generateMidiEvents();
};

} // namespace Infrastructure
} // namespace HAM