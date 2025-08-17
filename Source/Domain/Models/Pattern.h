#pragma once

// Pattern.h - Domain model for sequencer patterns
// Supports pattern morphing and JSON serialization

#include <string>
#include <vector>

namespace HAM {
namespace Domain {

/**
 * Represents a sequencer pattern with morphing capabilities
 * Contains pattern data and supports real-time interpolation
 */
class Pattern {
public:
    Pattern(const std::string& name = "Untitled Pattern");
    ~Pattern() = default;
    
    // Pattern metadata
    void setName(const std::string& name) { m_name = name; }
    const std::string& getName() const { return m_name; }
    
    void setTempo(float bpm) { m_tempo = bpm; }
    float getTempo() const { return m_tempo; }
    
    // Pattern morphing support
    void morphTo(const Pattern& target, float amount);
    
    // Serialization (JSON format as mentioned in README)
    std::string toJson() const;
    bool fromJson(const std::string& json);

private:
    std::string m_name;
    float m_tempo;
    
    // Pattern data would be stored here
    // For now, keeping it minimal
};

} // namespace Domain
} // namespace HAM