class Sound : public App::Window::Proceedable
{
public:
    Sound()
    {
		Initialize();
    }
    Sound(const wchar_t* const filePath)
    {
		Initialize();
        Load(filePath);
    }
    virtual ~Sound()
    {
		App::Window::RemoveProcedure(this);
	}
	void Load(const wchar_t* const filePath)
	{
		App::GetAudioDevice();

		ATL::CComPtr<IStream> stream = nullptr;
		SHCreateStreamOnFileW(filePath, STGM_READ, &stream);

		ATL::CComPtr<IMFByteStream> byteStream = nullptr;
		MFCreateMFByteStreamOnStream(stream, &byteStream);

		ATL::CComPtr<IMFAttributes> attributes = nullptr;
		MFCreateAttributes(&attributes, 1);

		sourceReader.Release();
		MFCreateSourceReaderFromByteStream(byteStream, attributes, &sourceReader);

		ATL::CComPtr<IMFMediaType> mediaType = nullptr;
		MFCreateMediaType(&mediaType);
		mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
		mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);

		sourceReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType);
		mediaType.Release();
		sourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &mediaType);

		UINT32 waveFormatSize = sizeof(WAVEFORMATEX);
		WAVEFORMATEX* waveFormat;
		MFCreateWaveFormatExFromMFMediaType(mediaType, &waveFormat, &waveFormatSize);

		ATL::CComPtr<IMFSample> sample = nullptr;
		DWORD flags = 0;
		sourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);

		ATL::CComPtr<IMFMediaBuffer> mediaBuffer = nullptr;
		sample->ConvertToContiguousBuffer(&mediaBuffer);

		mediaBuffer->GetMaxLength(&size);
		size -= waveFormat->nBlockAlign;

		DSBUFFERDESC bufferDesc = {};
		bufferDesc.dwSize = sizeof(DSBUFFERDESC);
		bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GETCURRENTPOSITION2;
		bufferDesc.dwBufferBytes = size * 2;
		bufferDesc.lpwfxFormat = waveFormat;

		soundBuffer.Release();
		App::GetAudioDevice().CreateSoundBuffer(&bufferDesc, &soundBuffer, nullptr);
	}
	void Play()
	{
		soundBuffer->Play(0, 0, DSBPLAY_LOOPING);
	}

private:
	ATL::CComPtr<IMFSourceReader> sourceReader = nullptr;
	ATL::CComPtr<IDirectSoundBuffer> soundBuffer = nullptr;
	DWORD size;
	int bufferIndex = 0;

	void Initialize()
	{
		App::Initialize();

		App::Window::AddProcedure(this);
	}
	void Push(void* buffer, DWORD size)
	{
		if (buffer == nullptr)
			return;

		memset(buffer, 128, size);

		ATL::CComPtr<IMFSample> sample = nullptr;
		DWORD flags = 0;
		sourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);

		if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
		{
			PROPVARIANT position = {};
			position.vt = VT_I8;
			position.hVal.QuadPart = 0;
			sourceReader->SetCurrentPosition(GUID_NULL, position);

			sample.Release();
			sourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);
		}

		ATL::CComPtr<IMFMediaBuffer> mediaBuffer = nullptr;
		sample->ConvertToContiguousBuffer(&mediaBuffer);

		DWORD wief;
		mediaBuffer->GetCurrentLength(&wief);

		mediaBuffer->SetCurrentLength(size);

		printf("%d %d\n", wief, size);

		BYTE* temp = nullptr;
		mediaBuffer->Lock(&temp, nullptr, &size);
		memcpy(buffer, temp, size);
		mediaBuffer->Unlock();
	}
	void OnProceed(HWND, UINT message, WPARAM, LPARAM) override
	{
		if (message != WM_APP)
			return;

		DWORD position;
		soundBuffer->GetCurrentPosition(&position, 0);

		void* buffer1 = nullptr;
		DWORD bufferSize1 = 0;
		void* buffer2 = nullptr;
		DWORD bufferSize2 = 0;

		if (bufferIndex == 0 && position < size)
		{
			soundBuffer->Lock(size, size * 2, &buffer1, &bufferSize1, &buffer2, &bufferSize2, 0);
			Push(buffer1, bufferSize1);
			soundBuffer->Unlock(buffer1, bufferSize1, buffer2, bufferSize2);
			bufferIndex = 1;
		}
		if (bufferIndex == 1 && position >= size)
		{
			soundBuffer->Lock(0, size, &buffer1, &bufferSize1, &buffer2, &bufferSize2, 0);
			Push(buffer1, bufferSize1);
			soundBuffer->Unlock(buffer1, bufferSize1, buffer2, bufferSize2);
			bufferIndex = 0;
		}
	}
};
