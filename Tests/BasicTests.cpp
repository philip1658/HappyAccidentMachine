#include <iostream>
#include <cassert>
#include "../Source/Domain/Models/Track.h"
#include "../Source/Domain/Models/Stage.h"
#include "../Source/Domain/Models/Pattern.h"
#include "../Source/Domain/Models/Scale.h"
#include "../Source/Domain/Engines/SequencerEngine.h"
#include "../Source/Domain/Engines/VoiceManager.h"
#include "../Source/Domain/Engines/AccumulatorEngine.h"

using namespace HAM::Domain;

void testTrackCreation() {
    std::cout << "🧪 Testing Track creation..." << std::endl;
    
    Track track;
    assert(track.getMidiChannel() == 1);
    assert(track.isEnabled() == true);
    assert(track.isMuted() == false);
    
    // Test stage access
    Stage& stage = track.getStage(0);
    assert(stage.isEnabled() == true);
    assert(stage.getPitch() == 0.0f);
    
    std::cout << "✅ Track tests passed" << std::endl;
}

void testSequencerEngine() {
    std::cout << "🧪 Testing SequencerEngine..." << std::endl;
    
    SequencerEngine engine;
    assert(engine.getTempo() == 120.0f);
    assert(engine.isPlaying() == false);
    
    engine.setTempo(140.0f);
    assert(engine.getTempo() == 140.0f);
    
    engine.play();
    assert(engine.isPlaying() == true);
    
    engine.stop();
    assert(engine.isPlaying() == false);
    
    std::cout << "✅ SequencerEngine tests passed" << std::endl;
}

void testVoiceManager() {
    std::cout << "🧪 Testing VoiceManager..." << std::endl;
    
    VoiceManager vm;
    assert(vm.getActiveVoiceCount() == 0);
    assert(vm.hasAvailableVoices() == true);
    
    // Allocate a voice
    int voiceIndex = vm.allocateVoice(60, 1, 0.8f);
    assert(voiceIndex >= 0);
    assert(vm.getActiveVoiceCount() == 1);
    
    // Release the voice
    vm.releaseVoice(voiceIndex);
    assert(vm.getActiveVoiceCount() == 0);
    
    std::cout << "✅ VoiceManager tests passed" << std::endl;
}

void testAccumulatorEngine() {
    std::cout << "🧪 Testing AccumulatorEngine..." << std::endl;
    
    AccumulatorEngine acc;
    assert(acc.getMode() == AccumulatorMode::NORMAL);
    
    // Test normal mode
    float result = acc.processStage(1.0f, 0);
    assert(result == 1.0f);
    
    // Test pendulum mode
    acc.setMode(AccumulatorMode::PENDULUM);
    assert(acc.getMode() == AccumulatorMode::PENDULUM);
    
    std::cout << "✅ AccumulatorEngine tests passed" << std::endl;
}

void testScales() {
    std::cout << "🧪 Testing Scale system..." << std::endl;
    
    Scale major = Scale::createMajor();
    assert(major.getName() == "Major");
    
    // Test quantization
    float quantized = major.quantizePitch(1.2f); // Should quantize to 2 (major second)
    assert(quantized == 2.0f);
    
    std::cout << "✅ Scale tests passed" << std::endl;
}

int main() {
    std::cout << "🎹 Running HAM Basic Tests" << std::endl;
    std::cout << "===========================" << std::endl;
    
    try {
        testTrackCreation();
        testSequencerEngine();
        testVoiceManager();
        testAccumulatorEngine();
        testScales();
        
        std::cout << std::endl;
        std::cout << "🎉 All tests passed!" << std::endl;
        std::cout << "✅ HAM core components are functional" << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ Test failed with unknown exception" << std::endl;
        return 1;
    }
}