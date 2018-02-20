class Audio {
	PROTECTED Microsoft::WRL::ComPtr<IXAudio2> audioEngine;
	PROTECTED IXAudio2MasteringVoice* masteringVoice = nullptr;

	PUBLIC Audio() {
		Initialize();
	}
	PUBLIC ~Audio() {
		MFShutdown();

		masteringVoice->DestroyVoice();
		
		audioEngine->StopEngine();
	}
	PROTECTED virtual void Initialize() {
		App::GetWindowHandle();

		XAudio2Create(audioEngine.GetAddressOf());

		audioEngine->CreateMasteringVoice(&masteringVoice);

		MFStartup(MF_VERSION);
	}
	PUBLIC IXAudio2& const GetEngine() const {
		return *audioEngine.Get();
	}
};
