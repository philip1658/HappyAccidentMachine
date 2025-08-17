cmake_minimum_required(VERSION 3.22)

project(HAM VERSION 0.1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build options
option(HAM_ENABLE_SQLITE "Enable SQLite-backed crash tracking" ON)
option(HAM_ENABLE_PLUGIN_SANDBOX "Enable plugin sandboxing" OFF)

# Find JUCE
find_package(PkgConfig REQUIRED)

# Create JUCE subdirectory if it doesn't exist
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/JUCE")
    message(STATUS "JUCE not found, you'll need to add it as a submodule or dependency")
    # For now, create a placeholder
    add_library(juce_core INTERFACE)
    add_library(juce_audio_utils INTERFACE)
    add_library(juce_audio_devices INTERFACE)
    add_library(juce_audio_formats INTERFACE)
    add_library(juce_audio_processors INTERFACE)
    add_library(juce_gui_basics INTERFACE)
    add_library(juce_gui_extra INTERFACE)
else()
    add_subdirectory(JUCE)
endif()

# HAM library
add_library(HAMLib
    Source/Domain/Models/Track.cpp
    Source/Domain/Models/Stage.cpp
    Source/Domain/Models/Pattern.cpp
    Source/Domain/Models/Scale.cpp
    Source/Domain/Engines/SequencerEngine.cpp
    Source/Domain/Engines/VoiceManager.cpp
    Source/Domain/Engines/AccumulatorEngine.cpp
    Source/Domain/Processors/MidiProcessor.cpp
    Source/Infrastructure/Audio/HamAudioProcessor.cpp
    Source/Presentation/Components/MainComponent.cpp
)

target_include_directories(HAMLib PUBLIC
    Source
    Source/Domain
    Source/Infrastructure
    Source/Presentation
)

# HAM standalone application
add_executable(HAM
    Source/Main.cpp
)

target_link_libraries(HAM PRIVATE
    HAMLib
    juce_core
    juce_audio_utils
    juce_audio_devices
    juce_audio_formats
    juce_audio_processors
    juce_gui_basics
    juce_gui_extra
)

# SQLite support
if(HAM_ENABLE_SQLITE)
    find_package(SQLite3 QUIET)
    if(SQLite3_FOUND)
        target_link_libraries(HAMLib PRIVATE SQLite::SQLite3)
        target_compile_definitions(HAMLib PRIVATE HAM_ENABLE_SQLITE=1)
    else()
        message(WARNING "SQLite3 not found, disabling SQLite support")
    endif()
endif()

# Plugin sandbox support
if(HAM_ENABLE_PLUGIN_SANDBOX)
    target_compile_definitions(HAMLib PRIVATE HAM_ENABLE_PLUGIN_SANDBOX=1)
endif()

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(HAMLib PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wno-unused-parameter
    )
endif()

# macOS specific settings
if(APPLE)
    set_target_properties(HAM PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.philip1658.HAM"
        MACOSX_BUNDLE_BUNDLE_NAME "HAM"
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
    )
endif()

# Testing
enable_testing()
add_subdirectory(Tests OPTIONAL)