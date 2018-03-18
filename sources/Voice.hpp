class Voice : public IXAudio2VoiceCallback
{
public:
    Voice()
    {
        App::Initialize();
    }
    Voice(const wchar_t* const filePath)
    {
        App::Initialize();
        Load(filePath);
    }
    ~Voice()
    {
        if (sourceVoice != nullptr)
            sourceVoice->DestroyVoice();
    }
    void Load(const wchar_t* const filePath)
    {
        App::GetAudioEngine();

        ATL::CComPtr<IStream> stream = nullptr;
        SHCreateStreamOnFileW(filePath, STGM_READ, &stream);

        ATL::CComPtr<IMFByteStream> byteStream = nullptr;
        MFCreateMFByteStreamOnStream(stream, &byteStream);

        ATL::CComPtr<IMFAttributes> attributes = nullptr;
        MFCreateAttributes(&attributes, 1);

        MFCreateSourceReaderFromByteStream(byteStream, attributes, &sourceReader);

        ATL::CComPtr<IMFMediaType> mediaType = nullptr;
        MFCreateMediaType(&mediaType);
        mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
        mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);

        sourceReader->SetCurrentMediaType(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), nullptr, mediaType);

        mediaType.Release();
        sourceReader->GetCurrentMediaType(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), &mediaType);

        UINT32 waveFormatSize = 0;
        WAVEFORMATEX* waveFormat;
        MFCreateWaveFormatExFromMFMediaType(mediaType, &waveFormat, &waveFormatSize);

        App::GetAudioEngine().CreateSourceVoice(&sourceVoice, waveFormat, XAUDIO2_VOICE_NOPITCH, 1.0f, this);
    }
    void Play()
    {
        if (sourceVoice == nullptr)
            return;

        sourceVoice->Start();
        SubmitBuffer();
    }

private:
    ATL::CComPtr<IMFSourceReader> sourceReader = nullptr;
    IXAudio2SourceVoice* sourceVoice = nullptr;

    void SubmitBuffer()
    {
        ATL::CComPtr<IMFSample> sample = nullptr;
        DWORD flags = 0;
        sourceReader->ReadSample(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, nullptr, &flags, nullptr, &sample);

        if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
        {
            PROPVARIANT position = {};
            position.vt = VT_I8;
            position.hVal.QuadPart = 0;
            sourceReader->SetCurrentPosition(GUID_NULL, position);

            sample.Release();
            sourceReader->ReadSample(static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, nullptr, &flags, nullptr, &sample);
        }

        ATL::CComPtr<IMFMediaBuffer> mediaBuffer = nullptr;
        sample->ConvertToContiguousBuffer(&mediaBuffer);

        DWORD audioDataLength = 0;
        BYTE* audioData;
        mediaBuffer->Lock(&audioData, nullptr, &audioDataLength);
        mediaBuffer->Unlock();

        XAUDIO2_BUFFER audioBuffer = {};
        audioBuffer.AudioBytes = audioDataLength;
        audioBuffer.pAudioData = audioData;
        sourceVoice->SubmitSourceBuffer(&audioBuffer);
    }
    void _stdcall OnBufferEnd(void*) override
    {
        SubmitBuffer();
    }
    void _stdcall OnBufferStart(void*) override
    {
    }
    void _stdcall OnLoopEnd(void*) override
    {
    }
    void _stdcall OnStreamEnd() override
    {
    }
    void _stdcall OnVoiceError(void*, HRESULT) override
    {
    }
    void _stdcall OnVoiceProcessingPassStart(UINT32) override
    {
    }
    void _stdcall OnVoiceProcessingPassEnd() override
    {
    }
};