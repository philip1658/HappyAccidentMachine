#pragma once

// AccumulatorEngine.h - Accumulator with PENDULUM mode for evolving melodies
// One of HAM's unique innovations

#include <atomic>

namespace HAM {
namespace Domain {

enum class AccumulatorMode {
    NORMAL,
    PENDULUM  // HAM's unique innovation
};

/**
 * Accumulator engine for evolving melodic patterns
 * PENDULUM mode creates unique melodic generation
 */
class AccumulatorEngine {
public:
    AccumulatorEngine();
    ~AccumulatorEngine() = default;
    
    // Real-time safe methods
    float processStage(float input, int stageIndex);
    void reset();
    
    // Configuration
    void setMode(AccumulatorMode mode);
    AccumulatorMode getMode() const;
    
    void setRange(float min, float max);
    float getMinRange() const;
    float getMaxRange() const;
    
    // Pendulum-specific settings
    void setPendulumSpeed(float speed);
    float getPendulumSpeed() const;

private:
    std::atomic<AccumulatorMode> m_mode;
    std::atomic<float> m_minRange;
    std::atomic<float> m_maxRange;
    std::atomic<float> m_pendulumSpeed;
    
    std::atomic<float> m_currentValue;
    std::atomic<float> m_pendulumDirection;
    std::atomic<int> m_stepCounter;
    
    float processPendulum(float input);
    float processNormal(float input);
};

} // namespace Domain
} // namespace HAM