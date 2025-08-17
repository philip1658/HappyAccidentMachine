#pragma once

// SequencerEngine.h - Core sequencer engine with real-time safety
// 24 PPQN timing resolution, lock-free design

#include <atomic>
#include <memory>
#include <vector>

namespace HAM {
namespace Domain {

class Track;

/**
 * Core sequencer engine with real-time safety guarantees
 * Processes tracks and generates MIDI events at 24 PPQN resolution
 */
class SequencerEngine {
public:
    static constexpr int MAX_TRACKS = 128;
    static constexpr int PPQN = 24; // Pulses Per Quarter Note
    
    SequencerEngine();
    ~SequencerEngine() = default;
    
    // Real-time safe methods (called from audio thread)
    void processNextPulse();
    void setTempo(float bpm);
    float getTempo() const;
    
    // Transport control
    void play();
    void stop();
    void pause();
    bool isPlaying() const;
    
    // Track management (not real-time safe)
    void addTrack(std::shared_ptr<Track> track);
    void removeTrack(int trackIndex);
    std::shared_ptr<Track> getTrack(int trackIndex) const;
    
    // Timing
    void reset();
    int getCurrentPulse() const;
    int getCurrentStep() const;

private:
    // Atomic members for real-time safety
    std::atomic<float> m_tempo;
    std::atomic<bool> m_isPlaying;
    std::atomic<int> m_currentPulse;
    
    // Non-atomic members (accessed only from non-RT thread)
    std::vector<std::shared_ptr<Track>> m_tracks;
    
    void processTrack(Track& track, int pulse);
};

} // namespace Domain
} // namespace HAM