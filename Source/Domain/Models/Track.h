#pragma once

// Track.h - Domain model for a sequencer track
// Part of HAM's Domain-Driven Design architecture

#include <vector>
#include <memory>

namespace HAM {
namespace Domain {

class Stage;
class Pattern;

/**
 * Represents a single sequencer track with 8 stages
 * Contains stage data, patterns, and track-level settings
 */
class Track {
public:
    static constexpr int MAX_STAGES = 8;
    static constexpr int MAX_TRACKS = 128;
    
    Track();
    ~Track() = default;
    
    // Stage management
    Stage& getStage(int stageIndex);
    const Stage& getStage(int stageIndex) const;
    
    // Pattern management
    void setPattern(std::shared_ptr<Pattern> pattern);
    std::shared_ptr<Pattern> getPattern() const;
    
    // Track properties
    void setMidiChannel(int channel) { m_midiChannel = channel; }
    int getMidiChannel() const { return m_midiChannel; }
    
    void setEnabled(bool enabled) { m_enabled = enabled; }
    bool isEnabled() const { return m_enabled; }
    
    void setMuted(bool muted) { m_muted = muted; }
    bool isMuted() const { return m_muted; }
    
    // Track color for UI
    void setTrackColor(int colorIndex) { m_trackColor = colorIndex; }
    int getTrackColor() const { return m_trackColor; }

private:
    std::vector<std::unique_ptr<Stage>> m_stages;
    std::shared_ptr<Pattern> m_pattern;
    
    int m_midiChannel;
    bool m_enabled;
    bool m_muted;
    int m_trackColor; // 0-7 for the 8 neon track colors
};

} // namespace Domain
} // namespace HAM