#include "SequencerEngine.h"
#include "../Models/Track.h"
#include "../Models/Stage.h"
#include <vector>

namespace HAM {
namespace Domain {

SequencerEngine::SequencerEngine()
    : m_tempo(120.0f)
    , m_isPlaying(false)
    , m_currentPulse(0)
{
    m_tracks.reserve(MAX_TRACKS);
}

void SequencerEngine::processNextPulse() {
    if (!m_isPlaying.load()) {
        return;
    }
    
    int currentPulse = m_currentPulse.load();
    
    // Process all tracks for this pulse
    for (auto& track : m_tracks) {
        if (track && track->isEnabled() && !track->isMuted()) {
            processTrack(*track, currentPulse);
        }
    }
    
    // Advance pulse counter
    m_currentPulse.store(currentPulse + 1);
}

void SequencerEngine::processTrack(Track& track, int pulse) {
    // Calculate which stage we're on (8 stages per track)
    int stageIndex = (pulse / (PPQN / 4)) % Track::MAX_STAGES; // 16th note per stage
    
    const auto& stage = track.getStage(stageIndex);
    
    if (stage.isEnabled()) {
        // Generate MIDI events based on stage parameters
        // This is where the actual MIDI generation would happen
        // For now, just a placeholder
        (void)stage; // Suppress unused variable warning
    }
}

void SequencerEngine::setTempo(float bpm) {
    m_tempo.store(bpm);
}

float SequencerEngine::getTempo() const {
    return m_tempo.load();
}

void SequencerEngine::play() {
    m_isPlaying.store(true);
}

void SequencerEngine::stop() {
    m_isPlaying.store(false);
    reset();
}

void SequencerEngine::pause() {
    m_isPlaying.store(false);
}

bool SequencerEngine::isPlaying() const {
    return m_isPlaying.load();
}

void SequencerEngine::addTrack(std::shared_ptr<Track> track) {
    if (m_tracks.size() < MAX_TRACKS) {
        m_tracks.push_back(track);
    }
}

void SequencerEngine::removeTrack(int trackIndex) {
    if (trackIndex >= 0 && trackIndex < static_cast<int>(m_tracks.size())) {
        m_tracks.erase(m_tracks.begin() + trackIndex);
    }
}

std::shared_ptr<Track> SequencerEngine::getTrack(int trackIndex) const {
    if (trackIndex >= 0 && trackIndex < static_cast<int>(m_tracks.size())) {
        return m_tracks[trackIndex];
    }
    return nullptr;
}

void SequencerEngine::reset() {
    m_currentPulse.store(0);
}

int SequencerEngine::getCurrentPulse() const {
    return m_currentPulse.load();
}

int SequencerEngine::getCurrentStep() const {
    return getCurrentPulse() / (PPQN / 4); // Convert pulses to 16th note steps
}

} // namespace Domain
} // namespace HAM