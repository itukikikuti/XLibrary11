class Voice : public IXAudio2VoiceCallback {
	PROTECTED Microsoft::WRL::ComPtr<IMFSourceReader> sourceReader;
	PROTECTED IXAudio2SourceVoice* sourceVoice;

	PUBLIC Voice(const wchar_t* const filePath) {
		Load(filePath);
	}
	PUBLIC ~Voice() {
		sourceVoice->DestroyVoice();
	}
	PUBLIC void Load(const wchar_t* const filePath) {
		App::GetAudioEngine();

		Microsoft::WRL::ComPtr<IStream> stream;
		SHCreateStreamOnFileW(filePath, STGM_READ, stream.GetAddressOf());

		Microsoft::WRL::ComPtr<IMFByteStream> byteStream;
		MFCreateMFByteStreamOnStream(stream.Get(), byteStream.GetAddressOf());

		Microsoft::WRL::ComPtr<IMFAttributes> attributes;
		MFCreateAttributes(attributes.GetAddressOf(), 1);

		MFCreateSourceReaderFromByteStream(byteStream.Get(), attributes.Get(), sourceReader.GetAddressOf());

		Microsoft::WRL::ComPtr<IMFMediaType> mediaType;
		MFCreateMediaType(mediaType.GetAddressOf());
		mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
		mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);

		sourceReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType.Get());

		mediaType.Reset();
		sourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, mediaType.GetAddressOf());

		UINT32 waveFormatSize = 0;
		WAVEFORMATEX* waveFormat;
		MFCreateWaveFormatExFromMFMediaType(mediaType.Get(), &waveFormat, &waveFormatSize);

		App::GetAudioEngine().CreateSourceVoice(&sourceVoice, waveFormat, XAUDIO2_VOICE_NOPITCH, 1.0f, this);
	}
	PUBLIC virtual void Play() {
		sourceVoice->Start();
		SubmitBuffer();
	}
	PROTECTED void SubmitBuffer() {
		Microsoft::WRL::ComPtr<IMFSample> sample;
		DWORD flags = 0;
		sourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, sample.GetAddressOf());

		if (flags & MF_SOURCE_READERF_ENDOFSTREAM) {
			PROPVARIANT position = {};
			position.vt = VT_I8;
			position.hVal.QuadPart = 0;
			sourceReader->SetCurrentPosition(GUID_NULL, position);

			sample.Reset();
			sourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, sample.GetAddressOf());
		}

		Microsoft::WRL::ComPtr<IMFMediaBuffer> mediaBuffer;
		sample->ConvertToContiguousBuffer(mediaBuffer.GetAddressOf());

		DWORD audioDataLength = 0;
		BYTE* audioData;
		mediaBuffer->Lock(&audioData, nullptr, &audioDataLength);
		mediaBuffer->Unlock();

		XAUDIO2_BUFFER audioBuffer = {};
		audioBuffer.AudioBytes = audioDataLength;
		audioBuffer.pAudioData = audioData;
		sourceVoice->SubmitSourceBuffer(&audioBuffer);
	}
	PROTECTED void _stdcall OnBufferEnd(void*) override {
		SubmitBuffer();
	}
	PRIVATE void _stdcall OnBufferStart(void*) override {
	}
	PRIVATE void _stdcall OnLoopEnd(void*) override {
	}
	PRIVATE void _stdcall OnStreamEnd() override {
	}
	PRIVATE void _stdcall OnVoiceError(void*, HRESULT) override {
	}
	PRIVATE void _stdcall OnVoiceProcessingPassStart(UINT32) override {
	}
	PRIVATE void _stdcall OnVoiceProcessingPassEnd() override {
	}
};
