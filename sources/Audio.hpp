class Audio
{
	PROTECTED ATL::CComPtr<IXAudio2> audioEngine;
	PROTECTED IXAudio2MasteringVoice* masteringVoice = nullptr;

	PUBLIC Audio()
	{
		App::Initialize();
		Initialize();
	}
	PUBLIC ~Audio()
	{
		MFShutdown();

		masteringVoice->DestroyVoice();
		
		audioEngine->StopEngine();
	}
	PROTECTED virtual void Initialize()
	{
		App::GetWindowHandle();

		XAudio2Create(&audioEngine);

		audioEngine->CreateMasteringVoice(&masteringVoice);

		MFStartup(MF_VERSION);
	}
	PUBLIC IXAudio2& GetEngine() const
	{
		return *audioEngine;
	}
};
