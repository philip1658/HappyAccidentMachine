# Jules[README.md](https://github.com/user-attachments/files/21824110/README.md)
# HAM - Happy Accident Machine
## 🎹 Overview

HAM is a high-performance MIDI sequencer that brings hardware-style sequencing to your DAW. Featuring an accumulator-based pitch system, advanced gate patterns, and real-time safe audio processing, HAM offers the tactile feel of hardware with the convenience of software.

**Current Status**: Alpha — Core engine implemented, UI functional, plugin system experimental  
**Latest Update**: Major refactoring completed (2025-08-11) - Improved code quality and DDD structure

### ✨ Key Features

#### Core Sequencing ✅
- **8-Stage Sequencing** per track with independent control
- **Accumulator Engine** with PENDULUM mode for evolving melodies
- **64-Voice Polyphony** with intelligent voice stealing (4 algorithms)
- **4 Gate Types** - MULTIPLE, HOLD, SINGLE, REST
- **Ratcheting** - Up to 8 subdivisions per pulse
- **Scale Quantization** - 16 preset scales + custom

#### Real-Time Performance ✅
- **Zero Allocations (design target)** - audio thread designed for zero allocations
- **Lock-Free Architecture (design)** - MIDI jitter minimized via lock-free queues
- **Low CPU (internal measurement)** - observed low CPU on Apple Silicon dev machine
- **Sample-Accurate** - 24 PPQN timing resolution

#### Professional Features ✅
- **Mixer** - 32-channel mixer with sends/returns
- **Plugin Hosting** - VST3/AU support with crash protection
- **Preset System** - JSON patterns, binary plugin states
- **Pattern Morphing** - Real-time interpolation between snapshots

#### Unique Innovation 🚀
- **Plugin Sandbox** (Beta) - Optional out-of-process plugin isolation
- **Crash Protection** - Automatic plugin quarantine after crashes
- **Smart Recovery** - Plugin health tracking with SQLite

---

## 🚀 Quick Start

### Prerequisites

- **macOS** 11.0 or later (Apple Silicon optimized)
- **CMake** 3.22 or later
- **Xcode** Command Line Tools
- **128MB** RAM minimum

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/philip1658/HAM.git
cd HAM

# Build and install to Desktop
./build.sh

# Launch the app
open ~/Desktop/HAM.app
```

Build options:
- Disable SQLite-backed crash tracking: pass `-DHAM_ENABLE_SQLITE=OFF` to CMake.
- Enable plugin sandboxing: pass `-DHAM_ENABLE_PLUGIN_SANDBOX=ON` to CMake.

---

## 🏗️ Architecture

HAM follows Domain-Driven Design principles with clean separation of concerns:

```
HAM/
├── Source/
│   ├── Domain/          # Business logic (UI-independent)
│   │   ├── Models/      # Track, Stage, Pattern, Scale
│   │   ├── Engines/     # Sequencer, Voice, Accumulator
│   │   └── Processors/  # MIDI generation, Pattern scheduling
│   ├── Infrastructure/  # Technical implementation
│   │   └── Audio/       # JUCE AudioProcessor
│   └── Presentation/    # UI Layer
│       └── Components/  # Pulse-style UI library
```

### 🔥 Performance Snapshot (internal dev machine)

| Metric | Target | Achieved | Status |
|--------|--------|----------|--------|
| **CPU Usage** | < 5% | indicative | ⚠️ |
| **MIDI Jitter** | < 0.1ms | indicative | ⚠️ |
| **Memory Allocations** | 0 in audio | target | ⚠️ |
| **Process Latency** | < 3ms | indicative | ⚠️ |
| **Plugin Sandbox Overhead** | < 1ms | experimental | ⚠️ |

See [Docs/REALTIME_SAFETY.md](Docs/REALTIME_SAFETY.md) for verification details.

---

## 🎨 User Interface

HAM features a meticulously crafted UI inspired by Pulse synthesizers:

- **Dark Void Aesthetic** - Minimal distractions
- **2x2 Slider Grid** - PITCH/PULSE/VEL/GATE per stage
- **Neon Accents** - 8 track colors for visual organization
- **Responsive Design** - All components fully scalable

### UI Designer Tool

An experimental UI Designer project exists under `Tools/UIDesigner` and may not be up to date with current components.

---

## 📚 Documentation

### Core Documentation
- [Docs/ARCHITECTURE.md](Docs/ARCHITECTURE.md) - System design and architecture
- [Docs/REALTIME_SAFETY.md](Docs/REALTIME_SAFETY.md) - Real-time guarantees and verification
- [Docs/TESTING.md](Docs/TESTING.md) - Testing guide and coverage
- [Docs/PERFORMANCE.md](Docs/PERFORMANCE.md) - Performance measurements and optimization

### Development Guides
- [ROADMAP.md](ROADMAP.md) - Development progress and milestones
- [CLAUDE.md](CLAUDE.md) - Developer guide and conventions
- [Docs/UI_DESIGN.md](Docs/UI_DESIGN.md) - Complete UI specifications
- [CHANGELOG.md](CHANGELOG.md) - Version history

---

## 🧪 Testing

HAM uses comprehensive unit testing with JUCE's UnitTest framework and CI/CD via GitHub Actions.

```bash
# Run all tests
cd build
ctest --output-on-failure

# Run specific test suite
./Tests/VoiceManagerTests
./Tests/SequencerEngineTests
./Tests/AccumulatorEngineTests

# Generate coverage report (requires lcov)
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="--coverage"
make && ctest
lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '/usr/*' '*/JUCE/*' --output-file coverage_filtered.info
genhtml coverage_filtered.info --output-directory coverage_report
```

### Test Status

| Test Suite | Status | Coverage |
|------------|--------|----------|
| **Unit Tests** | 15 suites | ~75% |
| **Integration Tests** | 5 suites | 
| **Performance Tests** | 4 suites 
| **CI/CD Pipeline** | GitHub Actions | 
| **Code Coverage** | lcov reporting | Tracked |

**Recent Improvements**:
- VoiceManager stability improvements
- CI/CD pipeline operational on macOS runners
- Expanded unit tests in Domain layer
- Initial performance regression hooks

---

## 🛠️ Development

### Code Style

```cpp
// Classes: PascalCase
class SequencerEngine {};

// Members: m_ prefix
float m_currentBpm;

// Functions: camelCase
void processNextStage();

// Constants: UPPER_SNAKE_CASE
const int MAX_TRACKS = 128;
```

### Real-Time Constraints

**Never in audio thread:**
- ❌ `new`/`delete` or `malloc`
- ❌ `std::mutex` or locks
- ❌ String operations
- ❌ File I/O

**Always use:**
- ✅ `std::atomic` for parameters
- ✅ Pre-allocated buffers
- ✅ Lock-free data structures

### Contributing

This is currently a private project. For collaboration inquiries, contact Philip Krieger.

---

## 📊 Project Status

**Current Phase**: Alpha hardening & optimization  
**Version**: 0.1.0-alpha  
**Overall Completion**: evolving towards v1.0  

### ✅ Completed Features

#### Core Engine (100%)
- Domain models and architecture
- MasterClock with 24 PPQN timing
- SequencerEngine with track processing
- VoiceManager with 64-voice polyphony
- All specialized engines (Gate, Pitch, Accumulator)
- Pattern morphing with caching

#### Audio Infrastructure (100%)
- Lock-free message queue
- Real-time safe processing design
- Zero allocations in audio thread
- MIDI routing and channel management

#### User Interface (90%)
- Complete Pulse-style component library (30+ components)
- Main sequencer interface
- Professional mixer with sends/returns
- Transport controls
- Plugin browser and management

#### Plugin System (80%)
- VST3/AU hosting
- Crash protection and tracking
- Optional out-of-process sandbox (beta)
- Window management

#### Testing & CI/CD (100%)
- GitHub Actions pipeline
- 15 test suites active
- Code coverage tracking
- Performance regression detection

### 🚧 In Progress
- Plugin Delay Compensation (design phase)
- Performance optimization (ongoing)
- Documentation completion

### 📅 Upcoming Features
- Multi-track UI scrolling
- MIDI Monitor integration
- Extended HAM Editor panel
- Scene manager UI
- Multi-core processing

---

## 🎯 What Makes HAM Unique

### Innovation Highlights
1. **Out-of-Process Plugin Sandbox** - Industry-first optional plugin isolation
2. **Accumulator with PENDULUM Mode** - Unique melodic generation
3. **Real-Time Safety Design** - Audio paths designed for real-time constraints
4. **Smart Plugin Management** - Automatic crash tracking and quarantine
5. **Professional Mixer Integration** - Full mixing console in a sequencer

### Technical Excellence
- **Test Coverage** tracked for critical paths
- **Zero-Allocation** design target for audio thread
- **Lock-Free** architecture throughout
- **< 0.1ms** MIDI timing accuracy target
- **Domain-Driven Design** for maintainability

## 🙏 Acknowledgments

- **JUCE Framework** - Cross-platform audio framework
- **Intellijel** - Inspiration from Metropolix hardware
- **Claude** - AI pair programming assistance
- **Philip Krieger** - Vision and direction

---

## 📄 License

Copyright © 2024-2025 Philip Krieger. All rights reserved.

This is proprietary software. Redistribution is not permitted without explicit written consent.

---

<div align="center">

**Built with ❤️ for the music production community**

[Report Bug](https://github.com/philip1658/HAM/issues) · [Request Feature](https://github.com/philip1658/HAM/issues)

</div>
