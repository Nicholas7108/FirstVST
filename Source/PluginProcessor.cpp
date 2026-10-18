#include <juce_audio_processors/juce_audio_processors.h>

class FirstVSTProcessor : public juce::AudioProcessor
{
public:
    FirstVSTProcessor()
        : AudioProcessor(
            BusesProperties()
                .withInput("Input", juce::AudioChannelSet::stereo(), true)
                .withOutput("Output", juce::AudioChannelSet::stereo(), true))
    {
        // The volume slider: ID, name, min, max, default.
        addParameter(gainParam = new juce::AudioParameterFloat(
            juce::ParameterID("gain", 1), "Volume", 0.0f, 1.0f, 0.5f));
    }

    void prepareToPlay(double, int) override {}
    void releaseResources() override {}

    bool isBusesLayoutSupported(const BusesLayout& layout) const override
    {
        auto output = layout.getMainOutputChannelSet();

        bool monoOrStereo =
            output == juce::AudioChannelSet::mono()
            || output == juce::AudioChannelSet::stereo();

        return monoOrStereo
            && output == layout.getMainInputChannelSet();
    }

    // This function changes the sound.
    void processBlock(juce::AudioBuffer<float>& buffer,
                      juce::MidiBuffer&) override
    {
        juce::ScopedNoDenormals noDenormals;

        buffer.applyGain(gainParam->get());
    }

    // Information the DAW needs about our plugin.
    const juce::String getName() const override { return "FirstVST"; }

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }

    double getTailLengthSeconds() const override { return 0.0; }

    // Show a window with a slider for every parameter.
    bool hasEditor() const override { return true; }

    juce::AudioProcessorEditor* createEditor() override
    {
        return new juce::GenericAudioProcessorEditor(*this);
    }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}

    const juce::String getProgramName(int) override
    {
        return "Default";
    }

    void changeProgramName(int, const juce::String&) override {}

    // Save and load the slider position (so FL Studio remembers it).
    void getStateInformation(juce::MemoryBlock& destData) override
    {
        juce::MemoryOutputStream stream(destData, true);
        stream.writeFloat(gainParam->get());
    }

    void setStateInformation(const void* data, int sizeInBytes) override
    {
        juce::MemoryInputStream stream(data, static_cast<size_t>(sizeInBytes), false);
        *gainParam = stream.readFloat();
    }

private:
    juce::AudioParameterFloat* gainParam = nullptr;
};

// JUCE calls this to create an instance of our plugin.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FirstVSTProcessor();
}
