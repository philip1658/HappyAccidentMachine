#include "VoiceManager.h"
#include <limits>

namespace HAM {
namespace Domain {

VoiceManager::VoiceManager()
    : m_stealingAlgorithm(VoiceStealingAlgorithm::OLDEST)
    , m_voiceCounter(0)
{
}

int VoiceManager::allocateVoice(int midiNote, int channel, float velocity) {
    // First try to find an available voice
    int voiceIndex = findAvailableVoice();
    
    if (voiceIndex >= 0) {
        // Found available voice
        Voice& voice = m_voices[voiceIndex];
        voice.midiNote.store(midiNote);
        voice.midiChannel.store(channel);
        voice.velocity.store(velocity);
        voice.age.store(m_voiceCounter.load());
        voice.active.store(true);
        
        return voiceIndex;
    }
    
    // No available voices, need to steal one
    return stealVoice(midiNote, channel, velocity);
}

void VoiceManager::releaseVoice(int voiceIndex) {
    if (voiceIndex >= 0 && voiceIndex < MAX_VOICES) {
        m_voices[voiceIndex].active.store(false);
        m_voices[voiceIndex].midiNote.store(-1);
    }
}

void VoiceManager::releaseNote(int midiNote, int channel) {
    for (int i = 0; i < MAX_VOICES; ++i) {
        Voice& voice = m_voices[i];
        if (voice.active.load() && 
            voice.midiNote.load() == midiNote && 
            voice.midiChannel.load() == channel) {
            releaseVoice(i);
            break; // Only release first matching voice
        }
    }
}

void VoiceManager::setStealingAlgorithm(VoiceStealingAlgorithm algorithm) {
    m_stealingAlgorithm.store(algorithm);
}

VoiceStealingAlgorithm VoiceManager::getStealingAlgorithm() const {
    return m_stealingAlgorithm.load();
}

Voice& VoiceManager::getVoice(int index) {
    return m_voices[index];
}

const Voice& VoiceManager::getVoice(int index) const {
    return m_voices[index];
}

int VoiceManager::getActiveVoiceCount() const {
    int count = 0;
    for (const auto& voice : m_voices) {
        if (voice.active.load()) {
            ++count;
        }
    }
    return count;
}

bool VoiceManager::hasAvailableVoices() const {
    return findAvailableVoice() >= 0;
}

void VoiceManager::updateAges() {
    m_voiceCounter.fetch_add(1);
}

int VoiceManager::findAvailableVoice() const {
    for (int i = 0; i < MAX_VOICES; ++i) {
        if (!m_voices[i].active.load()) {
            return i;
        }
    }
    return -1; // No available voices
}

int VoiceManager::stealVoice(int midiNote, int channel, float velocity) {
    int voiceIndex = -1;
    
    switch (m_stealingAlgorithm.load()) {
        case VoiceStealingAlgorithm::OLDEST:
            voiceIndex = findOldestVoice();
            break;
        case VoiceStealingAlgorithm::QUIETEST:
            voiceIndex = findQuietestVoice();
            break;
        case VoiceStealingAlgorithm::HIGHEST:
            voiceIndex = findHighestVoice();
            break;
        case VoiceStealingAlgorithm::LOWEST:
            voiceIndex = findLowestVoice();
            break;
    }
    
    if (voiceIndex >= 0) {
        Voice& voice = m_voices[voiceIndex];
        voice.midiNote.store(midiNote);
        voice.midiChannel.store(channel);
        voice.velocity.store(velocity);
        voice.age.store(m_voiceCounter.load());
        voice.active.store(true);
    }
    
    return voiceIndex;
}

int VoiceManager::findOldestVoice() const {
    int oldestIndex = -1;
    int oldestAge = std::numeric_limits<int>::max();
    
    for (int i = 0; i < MAX_VOICES; ++i) {
        if (m_voices[i].active.load()) {
            int age = m_voices[i].age.load();
            if (age < oldestAge) {
                oldestAge = age;
                oldestIndex = i;
            }
        }
    }
    
    return oldestIndex;
}

int VoiceManager::findQuietestVoice() const {
    int quietestIndex = -1;
    float quietestVelocity = std::numeric_limits<float>::max();
    
    for (int i = 0; i < MAX_VOICES; ++i) {
        if (m_voices[i].active.load()) {
            float velocity = m_voices[i].velocity.load();
            if (velocity < quietestVelocity) {
                quietestVelocity = velocity;
                quietestIndex = i;
            }
        }
    }
    
    return quietestIndex;
}

int VoiceManager::findHighestVoice() const {
    int highestIndex = -1;
    int highestNote = -1;
    
    for (int i = 0; i < MAX_VOICES; ++i) {
        if (m_voices[i].active.load()) {
            int note = m_voices[i].midiNote.load();
            if (note > highestNote) {
                highestNote = note;
                highestIndex = i;
            }
        }
    }
    
    return highestIndex;
}

int VoiceManager::findLowestVoice() const {
    int lowestIndex = -1;
    int lowestNote = 128; // Higher than any MIDI note
    
    for (int i = 0; i < MAX_VOICES; ++i) {
        if (m_voices[i].active.load()) {
            int note = m_voices[i].midiNote.load();
            if (note < lowestNote) {
                lowestNote = note;
                lowestIndex = i;
            }
        }
    }
    
    return lowestIndex;
}

} // namespace Domain
} // namespace HAM