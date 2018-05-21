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

        sourceReader->SetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType);
        mediaType.Release();
        sourceReader->GetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, &mediaType);

        UINT32 waveFormatSize = sizeof(WAVEFORMATEX);
        MFCreateWaveFormatExFromMFMediaType(mediaType, &format, &waveFormatSize);

        ATL::CComPtr<IMFSample> sample = nullptr;
        DWORD flags = 0;
        sourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);

        ATL::CComPtr<IMFMediaBuffer> mediaBuffer = nullptr;
        sample->ConvertToContiguousBuffer(&mediaBuffer);

        mediaBuffer->GetMaxLength(&bufferSize);
        bufferSize -= format->nBlockAlign;

        DSBUFFERDESC bufferDesc = {};
        bufferDesc.dwSize = sizeof(DSBUFFERDESC);
        bufferDesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GETCURRENTPOSITION2;
        bufferDesc.dwBufferBytes = bufferSize * 2;
        bufferDesc.lpwfxFormat = format;

        soundBuffer.Release();
        App::GetAudioDevice().CreateSoundBuffer(&bufferDesc, &soundBuffer, nullptr);
    }
    void SetLoop(bool isLoop)
    {
        properties.isLoop = isLoop;
    }
    void SetVolume(float volume)
    {
        if (volume < 0.00000001f)
            volume = 0.00000001f;

        LONG decibel = (LONG)(log10f(volume) * 20.0f * 100.0f);

        if (decibel < DSBVOLUME_MIN)
            decibel = DSBVOLUME_MIN;

        if (decibel > DSBVOLUME_MAX)
            decibel = DSBVOLUME_MAX;

        soundBuffer->SetVolume(decibel);
    }
    void SetPan(float pan)
    {
        int sign = (pan > 0) - (pan < 0);

        pan = 1.0f - fabsf(pan);
        if (pan < 0.00000001f)
            pan = 0.00000001f;

        LONG decibel = (LONG)(log10f(pan) * 20.0f * 100.0f) * -sign;

        if (decibel < DSBPAN_LEFT)
            decibel = DSBPAN_LEFT;

        if (decibel > DSBPAN_RIGHT)
            decibel = DSBPAN_RIGHT;

        soundBuffer->SetPan(decibel);
    }
    void SetPitch(float pitch)
    {
        if (pitch < 0.0f)
            pitch = 0.0f;

        DWORD frequency = (DWORD)(format->nSamplesPerSec * pitch);

        if (frequency < DSBFREQUENCY_MIN)
            frequency = DSBFREQUENCY_MIN;

        if (frequency > DSBFREQUENCY_MAX)
            frequency = DSBFREQUENCY_MAX;

        soundBuffer->SetFrequency(frequency);
    }
    void Play()
    {
        if (!properties.isLoop)
        {
            Stop();
        }

        state = play;
        soundBuffer->Play(0, 0, DSBPLAY_LOOPING);
    }
    void Pause()
    {
        state = pause;
        soundBuffer->Stop();
    }
    void Stop()
    {
        state = stop;
        Reset();

        bufferIndex = 0;
        soundBuffer->SetCurrentPosition(0);

        void* buffer = nullptr;
        DWORD bufferSize = 0;
        soundBuffer->Lock(0, 0, &buffer, &bufferSize, nullptr, nullptr, DSBLOCK_ENTIREBUFFER);
        memset(buffer, 256, bufferSize);
        soundBuffer->Unlock(buffer, bufferSize, nullptr, 0);
    }

private:
    enum State
    {
        play,
        pause,
        stop,
    };

    struct Properties
    {
        bool isLoop = false;
    }
    properties;

    ATL::CComPtr<IMFSourceReader> sourceReader = nullptr;
    ATL::CComPtr<IDirectSoundBuffer> soundBuffer = nullptr;
    DWORD bufferSize;
    int bufferIndex = 0;
    WAVEFORMATEX* format;
    State state = stop;

    void Initialize()
    {
        App::Initialize();

        App::Window::AddProcedure(this);
    }
    void Reset()
    {
        PROPVARIANT position = {};
        position.vt = VT_I8;
        position.hVal.QuadPart = 0;
        sourceReader->SetCurrentPosition(GUID_NULL, position);
    }
    void Push(void* buffer, DWORD size)
    {
        if (buffer == nullptr)
            return;

        memset(buffer, 256, size);

        ATL::CComPtr<IMFSample> sample = nullptr;
        DWORD flags = 0;
        sourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);

        if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
        {
            if (!properties.isLoop)
            {
                Stop();
                return;
            }

            Reset();

            sample.Release();
            sourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);
        }

        ATL::CComPtr<IMFMediaBuffer> mediaBuffer = nullptr;
        sample->ConvertToContiguousBuffer(&mediaBuffer);
        mediaBuffer->SetCurrentLength(size);

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

        if (state == stop)
        {
            void* buffer = nullptr;
            DWORD bufferSize = 0;
            soundBuffer->Lock(0, 0, &buffer, &bufferSize, nullptr, nullptr, DSBLOCK_ENTIREBUFFER);
            memset(buffer, 256, bufferSize);
            soundBuffer->Unlock(buffer, bufferSize, nullptr, 0);
        }
        else
        {
            void* buffer1 = nullptr;
            DWORD bufferSize1 = 0;
            void* buffer2 = nullptr;
            DWORD bufferSize2 = 0;

            if (bufferIndex == 0 && position < bufferSize)
            {
                soundBuffer->Lock(bufferSize, bufferSize * 2, &buffer1, &bufferSize1, &buffer2, &bufferSize2, 0);
                Push(buffer1, bufferSize1);
                soundBuffer->Unlock(buffer1, bufferSize1, buffer2, bufferSize2);
                bufferIndex = 1;
            }
            if (bufferIndex == 1 && position >= bufferSize)
            {
                soundBuffer->Lock(0, bufferSize, &buffer1, &bufferSize1, &buffer2, &bufferSize2, 0);
                Push(buffer1, bufferSize1);
                soundBuffer->Unlock(buffer1, bufferSize1, buffer2, bufferSize2);
                bufferIndex = 0;
            }
        }
    }
};
