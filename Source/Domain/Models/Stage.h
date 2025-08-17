#pragma once

// Stage.h - Domain model for a single sequencer stage
// Each track has 8 stages with PITCH/PULSE/VEL/GATE parameters

namespace HAM {
namespace Domain {

enum class GateType {
    MULTIPLE,
    HOLD,
    SINGLE,
    REST
};

/**
 * Represents a single stage in a sequencer track
 * Contains the 2x2 slider grid: PITCH/PULSE/VEL/GATE
 */
class Stage {
public:
    Stage();
    ~Stage() = default;
    
    // Core parameters (2x2 grid)
    void setPitch(float pitch) { m_pitch = pitch; }
    float getPitch() const { return m_pitch; }
    
    void setPulse(float pulse) { m_pulse = pulse; }
    float getPulse() const { return m_pulse; }
    
    void setVelocity(float velocity) { m_velocity = velocity; }
    float getVelocity() const { return m_velocity; }
    
    void setGate(float gate) { m_gate = gate; }
    float getGate() const { return m_gate; }
    
    // Gate type
    void setGateType(GateType type) { m_gateType = type; }
    GateType getGateType() const { return m_gateType; }
    
    // Ratcheting (up to 8 subdivisions)
    void setRatchetCount(int count) { m_ratchetCount = count; }
    int getRatchetCount() const { return m_ratchetCount; }
    
    // Stage enable/disable
    void setEnabled(bool enabled) { m_enabled = enabled; }
    bool isEnabled() const { return m_enabled; }

private:
    // Core 2x2 parameter grid
    float m_pitch;     // Pitch offset/value
    float m_pulse;     // Pulse probability/timing
    float m_velocity;  // MIDI velocity
    float m_gate;      // Gate length
    
    GateType m_gateType;
    int m_ratchetCount;
    bool m_enabled;
};

} // namespace Domain
} // namespace HAM