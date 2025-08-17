#pragma once

// MainComponent.h - Main UI component for HAM
// Pulse-style UI with dark void aesthetic

namespace HAM {
namespace Presentation {

/**
 * Main UI component for HAM
 * Features Pulse-style interface with dark void aesthetic
 */
class MainComponent {
public:
    MainComponent();
    virtual ~MainComponent();
    
    // Component lifecycle
    void initialize();
    void shutdown();
    
    // UI state
    void setVisible(bool visible) { m_visible = visible; }
    bool isVisible() const { return m_visible; }
    
    // Track colors (8 neon colors for visual organization)
    enum class TrackColor {
        RED = 0,
        ORANGE,
        YELLOW,
        GREEN,
        CYAN,
        BLUE,
        PURPLE,
        PINK
    };
    
    // Dark void aesthetic colors
    struct Colors {
        static constexpr unsigned int VOID_BLACK = 0xFF0A0A0A;
        static constexpr unsigned int NEON_RED = 0xFFFF3366;
        static constexpr unsigned int NEON_ORANGE = 0xFFFF8833;
        static constexpr unsigned int NEON_YELLOW = 0xFFFFCC33;
        static constexpr unsigned int NEON_GREEN = 0xFF33FF66;
        static constexpr unsigned int NEON_CYAN = 0xFF33CCFF;
        static constexpr unsigned int NEON_BLUE = 0xFF3366FF;
        static constexpr unsigned int NEON_PURPLE = 0xFF9933FF;
        static constexpr unsigned int NEON_PINK = 0xFFFF33CC;
    };

private:
    bool m_visible;
    
    void setupTrackGrid();
    void setupTransportControls();
    void setupMixer();
    
    unsigned int getTrackColor(TrackColor color) const;
};

} // namespace Presentation
} // namespace HAM