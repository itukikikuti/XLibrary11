class Audio {
	PROTECTED Microsoft::WRL::ComPtr<IXAudio2> audioEngine;
	PROTECTED IXAudio2MasteringVoice* masteringVoice = nullptr;

	PUBLIC Audio() {
		App::GetWindowHandle();

		XAudio2Create(audioEngine.GetAddressOf());

		audioEngine->CreateMasteringVoice(&masteringVoice);

		MFStartup(MF_VERSION);
	}
	PUBLIC ~Audio() {
		MFShutdown();

		masteringVoice->DestroyVoice();
		
		audioEngine->StopEngine();
	}
	PUBLIC IXAudio2& GetAudioEngine() {
		return *audioEngine.Get();
	}
};
