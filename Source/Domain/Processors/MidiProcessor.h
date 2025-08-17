#pragma once

// MidiProcessor.h - MIDI generation and routing
// Real-time safe MIDI event generation

#include <vector>
#include <atomic>

namespace HAM {
namespace Domain {

struct MidiEvent {
    int timestamp;
    int channel;
    int note;
    int velocity;
    bool isNoteOn;
};

/**
 * Processes MIDI events with real-time safety
 * Generates MIDI from sequencer data
 */
class MidiProcessor {
public:
    MidiProcessor();
    ~MidiProcessor() = default;
    
    // Real-time safe methods
    void processEvents(std::vector<MidiEvent>& outputEvents, int blockSize);
    void addNoteOn(int channel, int note, int velocity, int timestamp = 0);
    void addNoteOff(int channel, int note, int timestamp = 0);
    
    // Configuration
    void setChannelMapping(int track, int midiChannel);
    int getChannelMapping(int track) const;
    
    void clearEvents();

private:
    std::vector<MidiEvent> m_pendingEvents;
    std::vector<int> m_channelMapping; // Track to MIDI channel mapping
    
    void sortEventsByTimestamp();
};

} // namespace Domain
} // namespace HAM