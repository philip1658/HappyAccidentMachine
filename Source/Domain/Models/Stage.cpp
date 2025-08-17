#include "Stage.h"

namespace HAM {
namespace Domain {

Stage::Stage()
    : m_pitch(0.0f)
    , m_pulse(1.0f)     // Full probability by default
    , m_velocity(0.7f)  // 70% velocity by default
    , m_gate(0.5f)      // 50% gate length by default
    , m_gateType(GateType::SINGLE)
    , m_ratchetCount(1)
    , m_enabled(true)
{
}

} // namespace Domain
} // namespace HAM