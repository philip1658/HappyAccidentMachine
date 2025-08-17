#pragma once

// Scale.h - Domain model for musical scales and quantization

#include <vector>
#include <string>

namespace HAM {
namespace Domain {

/**
 * Musical scale for pitch quantization
 * Supports 16 preset scales + custom scales
 */
class Scale {
public:
    Scale(const std::string& name = "Chromatic");
    ~Scale() = default;
    
    // Scale metadata
    void setName(const std::string& name) { m_name = name; }
    const std::string& getName() const { return m_name; }
    
    // Scale notes (semitones from root)
    void setNotes(const std::vector<int>& notes) { m_notes = notes; }
    const std::vector<int>& getNotes() const { return m_notes; }
    
    // Quantize a pitch to the scale
    float quantizePitch(float pitch) const;
    
    // Preset scales
    static Scale createMajor();
    static Scale createMinor();
    static Scale createPentatonic();
    static Scale createChromatic();

private:
    std::string m_name;
    std::vector<int> m_notes; // Semitones from root
};

} // namespace Domain
} // namespace HAM