#pragma once

// VoiceManager.h - 64-voice polyphony with intelligent voice stealing
// Lock-free design for real-time safety

#include <atomic>
#include <array>

namespace HAM {
namespace Domain {

struct Voice {
    std::atomic<bool> active{false};
    std::atomic<int> midiNote{-1};
    std::atomic<int> midiChannel{1};
    std::atomic<float> velocity{0.0f};
    std::atomic<int> age{0}; // For voice stealing algorithms
};

enum class VoiceStealingAlgorithm {
    OLDEST,
    QUIETEST,
    HIGHEST,
    LOWEST
};

/**
 * Manages 64 voices with intelligent voice stealing
 * Real-time safe for audio thread usage
 */
class VoiceManager {
public:
    static constexpr int MAX_VOICES = 64;
    
    VoiceManager();
    ~VoiceManager() = default;
    
    // Real-time safe methods
    int allocateVoice(int midiNote, int channel, float velocity);
    void releaseVoice(int voiceIndex);
    void releaseNote(int midiNote, int channel);
    
    // Voice stealing
    void setStealingAlgorithm(VoiceStealingAlgorithm algorithm);
    VoiceStealingAlgorithm getStealingAlgorithm() const;
    
    // Voice access
    Voice& getVoice(int index);
    const Voice& getVoice(int index) const;
    
    // Statistics
    int getActiveVoiceCount() const;
    bool hasAvailableVoices() const;
    
    // Age counter update (called each audio block)
    void updateAges();

private:
    std::array<Voice, MAX_VOICES> m_voices;
    std::atomic<VoiceStealingAlgorithm> m_stealingAlgorithm;
    std::atomic<int> m_voiceCounter; // For age tracking
    
    int findAvailableVoice() const;
    int stealVoice(int midiNote, int channel, float velocity);
    int findOldestVoice() const;
    int findQuietestVoice() const;
    int findHighestVoice() const;
    int findLowestVoice() const;
};

} // namespace Domain
} // namespace HAM