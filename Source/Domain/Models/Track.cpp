#include "Track.h"
#include "Stage.h"
#include "Pattern.h"
#include <stdexcept>

namespace HAM {
namespace Domain {

Track::Track() 
    : m_midiChannel(1)
    , m_enabled(true)
    , m_muted(false)
    , m_trackColor(0)
{
    // Initialize 8 stages
    m_stages.reserve(MAX_STAGES);
    for (int i = 0; i < MAX_STAGES; ++i) {
        m_stages.emplace_back(std::make_unique<Stage>());
    }
}

Stage& Track::getStage(int stageIndex) {
    if (stageIndex < 0 || stageIndex >= MAX_STAGES) {
        throw std::out_of_range("Stage index out of range");
    }
    return *m_stages[stageIndex];
}

const Stage& Track::getStage(int stageIndex) const {
    if (stageIndex < 0 || stageIndex >= MAX_STAGES) {
        throw std::out_of_range("Stage index out of range");
    }
    return *m_stages[stageIndex];
}

void Track::setPattern(std::shared_ptr<Pattern> pattern) {
    m_pattern = pattern;
}

std::shared_ptr<Pattern> Track::getPattern() const {
    return m_pattern;
}

} // namespace Domain
} // namespace HAM