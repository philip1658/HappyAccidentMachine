#include "Scale.h"
#include <algorithm>
#include <cmath>

namespace HAM {
namespace Domain {

Scale::Scale(const std::string& name)
    : m_name(name)
    , m_notes{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11} // Chromatic by default
{
}

float Scale::quantizePitch(float pitch) const {
    if (m_notes.empty()) {
        return pitch;
    }
    
    // Simple quantization - find nearest scale note
    int semitone = static_cast<int>(std::round(pitch));
    int octave = semitone / 12;
    int note = semitone % 12;
    
    // Find closest note in scale
    auto it = std::lower_bound(m_notes.begin(), m_notes.end(), note);
    
    if (it == m_notes.end()) {
        // Wrap to next octave
        return static_cast<float>((octave + 1) * 12 + m_notes[0]);
    } else if (it == m_notes.begin()) {
        return static_cast<float>(octave * 12 + *it);
    } else {
        // Choose closer of the two adjacent notes
        auto prev = it - 1;
        if (note - *prev <= *it - note) {
            return static_cast<float>(octave * 12 + *prev);
        } else {
            return static_cast<float>(octave * 12 + *it);
        }
    }
}

Scale Scale::createMajor() {
    Scale scale("Major");
    scale.setNotes({0, 2, 4, 5, 7, 9, 11});
    return scale;
}

Scale Scale::createMinor() {
    Scale scale("Minor");
    scale.setNotes({0, 2, 3, 5, 7, 8, 10});
    return scale;
}

Scale Scale::createPentatonic() {
    Scale scale("Pentatonic");
    scale.setNotes({0, 2, 4, 7, 9});
    return scale;
}

Scale Scale::createChromatic() {
    Scale scale("Chromatic");
    scale.setNotes({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
    return scale;
}

} // namespace Domain
} // namespace HAM