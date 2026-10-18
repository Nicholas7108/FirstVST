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

        float gain = 0.5f;
        buffer.applyGain(gain);
    }

    // Information the DAW needs about our plugin.
    const juce::String getName() const override { return "FirstVST"; }

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }

    double getTailLengthSeconds() const override { return 0.0; }

    bool hasEditor() const override { return false; }

    juce::AudioProcessorEditor* createEditor() override
    {
        return nullptr;
    }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}

    const juce::String getProgramName(int) override
    {
        return "Default";
    }

    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock&) override {}
    void setStateInformation(const void*, int) override {}
};

// JUCE calls this to create an instance of our plugin.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FirstVSTProcessor();
}