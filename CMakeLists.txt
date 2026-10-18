cmake_minimum_required(VERSION 3.24)

project(FirstVST VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download JUCE on the build machine
include(FetchContent)

FetchContent_Declare(JUCE
    URL https://github.com/juce-framework/JUCE/archive/refs/tags/9.0.4.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP FALSE
)

FetchContent_MakeAvailable(JUCE)

# Describe our plugin
juce_add_plugin(FirstVST
    COMPANY_NAME "MyAudio"
    PLUGIN_MANUFACTURER_CODE Myau
    PLUGIN_CODE Fvst
    PRODUCT_NAME "FirstVST"
    FORMATS VST3
    IS_SYNTH FALSE
    NEEDS_WEB_BROWSER FALSE
    NEEDS_CURL FALSE
)

# Our C++ source file
target_sources(FirstVST PRIVATE
    Source/PluginProcessor.cpp
)

# Disable features this simple plugin does not need
target_compile_definitions(FirstVST PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

# Connect our code to JUCE
target_link_libraries(FirstVST PRIVATE
    juce::juce_audio_processors
    juce::juce_recommended_config_flags
)