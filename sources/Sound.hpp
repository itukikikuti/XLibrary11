class Sound : public Window::Proceedable
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
        Window::RemoveProcedure(this);
    }
    void Load(const wchar_t* const filePath)
    {
        Audio::GetDevice();

        ComPtr<IStream> stream = nullptr;
        SHCreateStreamOnFileW(filePath, STGM_READ, stream.GetAddressOf());

        ComPtr<IMFByteStream> byteStream = nullptr;
        MFCreateMFByteStreamOnStream(stream.Get(), byteStream.GetAddressOf());

        ComPtr<IMFAttributes> attributes = nullptr;
        MFCreateAttributes(attributes.GetAddressOf(), 1);

        _sourceReader.Reset();
        MFCreateSourceReaderFromByteStream(byteStream.Get(), attributes.Get(), _sourceReader.GetAddressOf());

        ComPtr<IMFMediaType> mediaType = nullptr;
        MFCreateMediaType(mediaType.GetAddressOf());
        mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
        mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);

        _sourceReader->SetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType.Get());
        mediaType.Reset();
        _sourceReader->GetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, mediaType.GetAddressOf());

        UINT32 waveFormatSize = sizeof(WAVEFORMATEX);
        MFCreateWaveFormatExFromMFMediaType(mediaType.Get(), &_format, &waveFormatSize);

        ComPtr<IMFSample> sample = nullptr;
        DWORD flags = 0;
        _sourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, sample.GetAddressOf());

        ComPtr<IMFMediaBuffer> mediaBuffer = nullptr;
        sample->ConvertToContiguousBuffer(mediaBuffer.GetAddressOf());

        mediaBuffer->GetMaxLength(&_bufferSize);
        _bufferSize -= _format->nBlockAlign;

        DSBUFFERDESC bufferDesc = {};
        bufferDesc.dwSize = sizeof(DSBUFFERDESC);
        bufferDesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GETCURRENTPOSITION2;
        bufferDesc.dwBufferBytes = _bufferSize * 2;
        bufferDesc.lpwfxFormat = _format;

        _soundBuffer.Reset();
        Audio::GetDevice().CreateSoundBuffer(&bufferDesc, _soundBuffer.GetAddressOf(), nullptr);
    }
    void SetLoop(bool isLoop)
    {
        _isLoop = isLoop;
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

        _soundBuffer->SetVolume(decibel);
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

        _soundBuffer->SetPan(decibel);
    }
    void SetPitch(float pitch)
    {
        if (pitch < 0.0f)
            pitch = 0.0f;

        DWORD frequency = (DWORD)(_format->nSamplesPerSec * pitch);

        if (frequency < DSBFREQUENCY_MIN)
            frequency = DSBFREQUENCY_MIN;

        if (frequency > DSBFREQUENCY_MAX)
            frequency = DSBFREQUENCY_MAX;

        _soundBuffer->SetFrequency(frequency);
    }
    void Play()
    {
        if (!_isLoop)
        {
            Stop();
        }

        _state = play;
        _soundBuffer->Play(0, 0, DSBPLAY_LOOPING);
    }
    void Pause()
    {
        _state = pause;
        _soundBuffer->Stop();
    }
    void Stop()
    {
        _state = stop;
        Reset();

        _bufferIndex = 0;
        _soundBuffer->SetCurrentPosition(0);

        void* buffer = nullptr;
        DWORD bufferSize = 0;
        _soundBuffer->Lock(0, 0, &buffer, &bufferSize, nullptr, nullptr, DSBLOCK_ENTIREBUFFER);
        memset(buffer, 256, bufferSize);
        _soundBuffer->Unlock(buffer, bufferSize, nullptr, 0);
    }

private:
    enum State
    {
        play,
        pause,
        stop,
    };

    ComPtr<IMFSourceReader> _sourceReader = nullptr;
    ComPtr<IDirectSoundBuffer> _soundBuffer = nullptr;
    DWORD _bufferSize;
    int _bufferIndex = 0;
    WAVEFORMATEX* _format;
    State _state = stop;
    bool _isLoop = false;

    void Initialize()
    {
        InitializeApplication();

        Window::AddProcedure(this);
    }
    void Reset()
    {
        PROPVARIANT position = {};
        position.vt = VT_I8;
        position.hVal.QuadPart = 0;
        _sourceReader->SetCurrentPosition(GUID_NULL, position);
    }
    void Push(void* buffer, DWORD size)
    {
        if (buffer == nullptr)
            return;

        memset(buffer, 256, size);

        ComPtr<IMFSample> sample = nullptr;
        DWORD flags = 0;
        _sourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, sample.GetAddressOf());

        if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
        {
            if (!_isLoop)
            {
                Stop();
                return;
            }

            Reset();

            sample.Reset();
            _sourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, sample.GetAddressOf());
        }

        ComPtr<IMFMediaBuffer> mediaBuffer = nullptr;
        sample->ConvertToContiguousBuffer(mediaBuffer.GetAddressOf());
        mediaBuffer->SetCurrentLength(size);

        BYTE* temp = nullptr;
        mediaBuffer->Lock(&temp, nullptr, &size);
        memcpy(buffer, temp, size);
        mediaBuffer->Unlock();
    }
    void OnProceedMessage(HWND, UINT message, WPARAM, LPARAM) override
    {
        if (message != WM_APP)
            return;

        DWORD position;
        _soundBuffer->GetCurrentPosition(&position, 0);

        if (_state == stop)
        {
            void* buffer = nullptr;
            DWORD bufferSize = 0;
            _soundBuffer->Lock(0, 0, &buffer, &bufferSize, nullptr, nullptr, DSBLOCK_ENTIREBUFFER);
            memset(buffer, 256, bufferSize);
            _soundBuffer->Unlock(buffer, bufferSize, nullptr, 0);
        }
        else
        {
            void* buffer1 = nullptr;
            DWORD bufferSize1 = 0;
            void* buffer2 = nullptr;
            DWORD bufferSize2 = 0;

            if (_bufferIndex == 0 && position < _bufferSize)
            {
                _soundBuffer->Lock(_bufferSize, _bufferSize * 2, &buffer1, &bufferSize1, &buffer2, &bufferSize2, 0);
                Push(buffer1, bufferSize1);
                _soundBuffer->Unlock(buffer1, bufferSize1, buffer2, bufferSize2);
                _bufferIndex = 1;
            }
            if (_bufferIndex == 1 && position >= _bufferSize)
            {
                _soundBuffer->Lock(0, _bufferSize, &buffer1, &bufferSize1, &buffer2, &bufferSize2, 0);
                Push(buffer1, bufferSize1);
                _soundBuffer->Unlock(buffer1, bufferSize1, buffer2, bufferSize2);
                _bufferIndex = 0;
            }
        }
    }
};
