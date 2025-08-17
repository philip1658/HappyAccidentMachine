#include "AccumulatorEngine.h"
#include <algorithm>
#include <cmath>

namespace HAM {
namespace Domain {

AccumulatorEngine::AccumulatorEngine()
    : m_mode(AccumulatorMode::NORMAL)
    , m_minRange(-12.0f)  // -1 octave
    , m_maxRange(12.0f)   // +1 octave  
    , m_pendulumSpeed(1.0f)
    , m_currentValue(0.0f)
    , m_pendulumDirection(1.0f)
    , m_stepCounter(0)
{
}

float AccumulatorEngine::processStage(float input, int stageIndex) {
    (void)stageIndex; // May be used for per-stage processing in the future
    
    switch (m_mode.load()) {
        case AccumulatorMode::PENDULUM:
            return processPendulum(input);
        case AccumulatorMode::NORMAL:
        default:
            return processNormal(input);
    }
}

float AccumulatorEngine::processPendulum(float input) {
    // PENDULUM mode - HAM's unique innovation
    // Creates a pendulum-like motion that evolves the melody
    
    float speed = m_pendulumSpeed.load();
    float direction = m_pendulumDirection.load();
    float current = m_currentValue.load();
    
    // Apply pendulum motion
    float pendulumOffset = std::sin(m_stepCounter.load() * speed * 0.1f) * direction;
    float newValue = current + input + pendulumOffset;
    
    // Clamp to range and reverse direction if needed
    float minRange = m_minRange.load();
    float maxRange = m_maxRange.load();
    
    if (newValue > maxRange) {
        newValue = maxRange;
        m_pendulumDirection.store(-direction);
    } else if (newValue < minRange) {
        newValue = minRange;
        m_pendulumDirection.store(-direction);
    }
    
    m_currentValue.store(newValue);
    m_stepCounter.fetch_add(1);
    
    return newValue;
}

float AccumulatorEngine::processNormal(float input) {
    float current = m_currentValue.load();
    float newValue = current + input;
    
    // Clamp to range
    float minRange = m_minRange.load();
    float maxRange = m_maxRange.load();
    newValue = std::clamp(newValue, minRange, maxRange);
    
    m_currentValue.store(newValue);
    
    return newValue;
}

void AccumulatorEngine::reset() {
    m_currentValue.store(0.0f);
    m_pendulumDirection.store(1.0f);
    m_stepCounter.store(0);
}

void AccumulatorEngine::setMode(AccumulatorMode mode) {
    m_mode.store(mode);
}

AccumulatorMode AccumulatorEngine::getMode() const {
    return m_mode.load();
}

void AccumulatorEngine::setRange(float min, float max) {
    m_minRange.store(min);
    m_maxRange.store(max);
}

float AccumulatorEngine::getMinRange() const {
    return m_minRange.load();
}

float AccumulatorEngine::getMaxRange() const {
    return m_maxRange.load();
}

void AccumulatorEngine::setPendulumSpeed(float speed) {
    m_pendulumSpeed.store(speed);
}

float AccumulatorEngine::getPendulumSpeed() const {
    return m_pendulumSpeed.load();
}

} // namespace Domain
} // namespace HAM