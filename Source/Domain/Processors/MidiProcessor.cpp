#include "MidiProcessor.h"
#include <algorithm>

namespace HAM {
namespace Domain {

MidiProcessor::MidiProcessor() {
    // Initialize with default channel mapping (1:1)
    m_channelMapping.resize(128);
    for (int i = 0; i < 128; ++i) {
        m_channelMapping[i] = (i % 16) + 1; // MIDI channels 1-16
    }
}

void MidiProcessor::processEvents(std::vector<MidiEvent>& outputEvents, int blockSize) {
    (void)blockSize; // May be used for sample-accurate timing
    
    // Sort events by timestamp for sample-accurate playback
    sortEventsByTimestamp();
    
    // Copy pending events to output
    outputEvents.insert(outputEvents.end(), m_pendingEvents.begin(), m_pendingEvents.end());
    
    // Clear processed events
    m_pendingEvents.clear();
}

void MidiProcessor::addNoteOn(int channel, int note, int velocity, int timestamp) {
    MidiEvent event;
    event.timestamp = timestamp;
    event.channel = channel;
    event.note = note;
    event.velocity = velocity;
    event.isNoteOn = true;
    
    m_pendingEvents.push_back(event);
}

void MidiProcessor::addNoteOff(int channel, int note, int timestamp) {
    MidiEvent event;
    event.timestamp = timestamp;
    event.channel = channel;
    event.note = note;
    event.velocity = 0;
    event.isNoteOn = false;
    
    m_pendingEvents.push_back(event);
}

void MidiProcessor::setChannelMapping(int track, int midiChannel) {
    if (track >= 0 && track < static_cast<int>(m_channelMapping.size())) {
        m_channelMapping[track] = midiChannel;
    }
}

int MidiProcessor::getChannelMapping(int track) const {
    if (track >= 0 && track < static_cast<int>(m_channelMapping.size())) {
        return m_channelMapping[track];
    }
    return 1; // Default to channel 1
}

void MidiProcessor::clearEvents() {
    m_pendingEvents.clear();
}

void MidiProcessor::sortEventsByTimestamp() {
    std::sort(m_pendingEvents.begin(), m_pendingEvents.end(),
        [](const MidiEvent& a, const MidiEvent& b) {
            return a.timestamp < b.timestamp;
        });
}

} // namespace Domain
} // namespace HAM