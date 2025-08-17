# Project Structure

This document describes the current HAM project structure after initial setup.

## Directory Layout

```
HAM/
├── Source/                     # All source code
│   ├── Domain/                 # Business logic (UI-independent)
│   │   ├── Models/             # Track, Stage, Pattern, Scale
│   │   │   ├── Track.h/.cpp    # 8-stage sequencer tracks
│   │   │   ├── Stage.h/.cpp    # Individual stages with PITCH/PULSE/VEL/GATE
│   │   │   ├── Pattern.h/.cpp  # Pattern management and morphing
│   │   │   └── Scale.h/.cpp    # Musical scales and quantization
│   │   ├── Engines/            # Core processing engines
│   │   │   ├── SequencerEngine.h/.cpp    # Main sequencer with 24 PPQN
│   │   │   ├── VoiceManager.h/.cpp       # 64-voice polyphony manager
│   │   │   └── AccumulatorEngine.h/.cpp  # Accumulator with PENDULUM mode
│   │   └── Processors/         # MIDI and pattern processing
│   │       └── MidiProcessor.h/.cpp      # MIDI event generation
│   ├── Infrastructure/         # Technical implementation
│   │   └── Audio/             # Audio framework integration
│   │       └── HamAudioProcessor.h/.cpp  # JUCE bridge
│   └── Presentation/          # UI Layer
│       └── Components/        # UI components
│           └── MainComponent.h/.cpp      # Main UI with Pulse aesthetic
├── Tests/                     # Unit tests
│   ├── CMakeLists.txt        # Test configuration
│   └── BasicTests.cpp        # Core component tests
├── build/                    # Build artifacts (gitignored)
├── CMakeLists.txt            # Main CMake configuration
├── build.sh                  # Cross-platform build script
├── .gitignore               # Git ignore patterns
└── README.md                # Main documentation
```

## Current Status

✅ **Buildable**: The project compiles successfully on Linux and should work on macOS
✅ **Testable**: Basic unit tests verify core functionality
✅ **Runnable**: HAM executable launches and displays status
✅ **Configurable**: Build options work (SQLite, Plugin Sandbox)

## Build Requirements Met

- CMake 3.22+ ✅
- C++17 standard ✅  
- Cross-platform build script ✅
- Build options for features ✅
- Basic test suite ✅

## Architecture Implemented

The Domain-Driven Design architecture is in place:

1. **Domain Layer**: Pure business logic, no external dependencies
2. **Infrastructure Layer**: Technical concerns (audio, MIDI)
3. **Presentation Layer**: UI components with Pulse aesthetic

## Real-Time Safety Design

- Atomic variables for thread-safe parameter access
- Lock-free data structures where possible
- Pre-allocated buffers (design target)
- No allocations in audio thread (design target)

## Next Steps for Full Implementation

1. Add JUCE framework integration
2. Implement actual audio processing
3. Build complete UI with JUCE components
4. Add plugin hosting system
5. Implement pattern morphing
6. Add comprehensive test coverage