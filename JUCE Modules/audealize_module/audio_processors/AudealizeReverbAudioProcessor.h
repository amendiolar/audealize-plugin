#ifndef AUDEALIZEREVERBAUDIOPROCESSOR_H_INCLUDED
#define AUDEALIZEREVERBAUDIOPROCESSOR_H_INCLUDED

namespace Audealize
{
/// AudealizeAudioProcessor for reverb effect
class AudealizereverbAudioProcessor : public AudealizeAudioProcessor
{
public:
    AudealizereverbAudioProcessor (AudealizeAudioProcessor* owner = nullptr);
    ~AudealizereverbAudioProcessor ();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources () override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
#endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    AudealizeUI* createEditorForMultiEffect ();

    AudioProcessorEditor* createEditor () override;

    bool hasEditor () const override;

    const String getName () const override;

    bool acceptsMidi () const override;
    bool producesMidi () const override;
    double getTailLengthSeconds () const override;

    int getNumPrograms () override;
    int getCurrentProgram () override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    void parameterChanged (const juce::String& parameterID, float newValue) override;

    void settingsFromMap (vector<float> settings) override;

    inline String getParamID (int index) override;

    inline int getParamIdx (String paramId);

    /**
     * Enumerate parameter indices for easy vector access
     */
    enum Parameters
    {
        kParamD,
        kParamG,
        kParamM,
        kParamF,
        kParamE,
        kParamAmount,
        kNumParams
    };

    /**
     *  String parameter Ids
     */
    static String paramD;
    static String paramG;
    static String paramM;
    static String paramF;
    static String paramE;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudealizereverbAudioProcessor)

    Audealize::Reverb mReverb;

    NormalisableRange<float> mParamRange[kNumParams];

    LinearSmoothedValue<float> mSmoothedVals[kNumParams];

    const float DEFAULT_D = 0.05f;
    const float DEFAULT_G = 0.5f;
    const float DEFAULT_M = 0.005f;
    const float DEFAULT_F = 5500.0f;
    const float DEFAULT_E = 0.95f;
    const float DEFAULT_MIX = 0.75f;

    void debugParams ();
};
}
#endif  // AUDEALIZEREVERBAUDIOPROCESSOR_H_INCLUDED