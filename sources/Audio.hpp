class Audio
{
public:
    Audio()
    {
        App::Initialize();

        App::GetWindowHandle();

        XAudio2Create(&audioEngine);

        audioEngine->CreateMasteringVoice(&masteringVoice);

        MFStartup(MF_VERSION);
    }
    ~Audio()
    {
        MFShutdown();

        masteringVoice->DestroyVoice();

        audioEngine->StopEngine();
    }
    IXAudio2& GetEngine() const
    {
        return *audioEngine;
    }

private:
    ATL::CComPtr<IXAudio2> audioEngine = nullptr;
    IXAudio2MasteringVoice* masteringVoice = nullptr;
};