class Audio
{
public:
	Audio()
	{
		App::Initialize();
		Initialize();
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
	ATL::CComPtr<IXAudio2> audioEngine;
	IXAudio2MasteringVoice* masteringVoice = nullptr;

	virtual void Initialize()
	{
		App::GetWindowHandle();

		XAudio2Create(&audioEngine);

		audioEngine->CreateMasteringVoice(&masteringVoice);

		MFStartup(MF_VERSION);
	}
};