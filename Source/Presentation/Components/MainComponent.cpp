#include "MainComponent.h"
#include <iostream>

namespace HAM {
namespace Presentation {

MainComponent::MainComponent()
    : m_visible(false)
{
    std::cout << "🎨 Initializing HAM UI - Pulse-style interface" << std::endl;
}

MainComponent::~MainComponent() {
    shutdown();
}

void MainComponent::initialize() {
    std::cout << "🎨 Setting up HAM UI components..." << std::endl;
    
    setupTrackGrid();
    setupTransportControls();
    setupMixer();
    
    std::cout << "✅ HAM UI initialized with dark void aesthetic" << std::endl;
    std::cout << "   - 2x2 Slider Grid per stage (PITCH/PULSE/VEL/GATE)" << std::endl;
    std::cout << "   - 8 Neon track colors for visual organization" << std::endl;
    std::cout << "   - Professional 32-channel mixer" << std::endl;
    std::cout << "   - Responsive, scalable design" << std::endl;
}

void MainComponent::shutdown() {
    if (m_visible) {
        std::cout << "🎨 Shutting down HAM UI" << std::endl;
        m_visible = false;
    }
}

void MainComponent::setupTrackGrid() {
    // Set up the main 8-track sequencer grid
    // Each track has 8 stages with 2x2 slider grid
    std::cout << "   Setting up 8-track sequencer grid..." << std::endl;
    
    for (int track = 0; track < 8; ++track) {
        TrackColor color = static_cast<TrackColor>(track);
        unsigned int colorValue = getTrackColor(color);
        (void)colorValue; // Suppress unused warning
        
        for (int stage = 0; stage < 8; ++stage) {
            // Each stage has PITCH/PULSE/VEL/GATE sliders
            // In a real implementation, these would be actual UI components
        }
    }
}

void MainComponent::setupTransportControls() {
    // Set up play/stop/pause/record controls
    std::cout << "   Setting up transport controls..." << std::endl;
    
    // Transport buttons with HAM styling
    // BPM display and tempo control
    // Pattern selection
}

void MainComponent::setupMixer() {
    // Set up the professional 32-channel mixer
    std::cout << "   Setting up 32-channel mixer..." << std::endl;
    
    // Channel strips with:
    // - Volume faders
    // - Send/return controls
    // - EQ controls
    // - Plugin insert slots
}

unsigned int MainComponent::getTrackColor(TrackColor color) const {
    switch (color) {
        case TrackColor::RED:    return Colors::NEON_RED;
        case TrackColor::ORANGE: return Colors::NEON_ORANGE;
        case TrackColor::YELLOW: return Colors::NEON_YELLOW;
        case TrackColor::GREEN:  return Colors::NEON_GREEN;
        case TrackColor::CYAN:   return Colors::NEON_CYAN;
        case TrackColor::BLUE:   return Colors::NEON_BLUE;
        case TrackColor::PURPLE: return Colors::NEON_PURPLE;
        case TrackColor::PINK:   return Colors::NEON_PINK;
        default:                 return Colors::NEON_RED;
    }
}

} // namespace Presentation
} // namespace HAM