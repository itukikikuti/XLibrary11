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
    ~Sound()
    {
        App::Window::RemoveProcedure(this);
    }
    void Load(const wchar_t* const filePath)
    {
        graphBuilder.CoCreateInstance(CLSID_FilterGraph, nullptr, CLSCTX_INPROC);
        graphBuilder->RenderFile(filePath, nullptr);

        graphBuilder->QueryInterface(IID_IMediaControl, reinterpret_cast<void**>(&mediaControl));
        graphBuilder->QueryInterface(IID_IMediaSeeking, reinterpret_cast<void**>(&mediaSeeking));
        graphBuilder->QueryInterface(IID_IMediaEventEx, reinterpret_cast<void**>(&mediaEvent));

        mediaSeeking->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
        mediaEvent->SetNotifyWindow((OAHWND)App::GetWindowHandle(), WM_APP, 0);
    }
    void SetLoop(bool isLoop)
    {
        this->isLoop = isLoop;
    }
    void SetVolume(float volume)
    {
    }
    void Play()
    {
        if (graphBuilder == nullptr)
            return;

        if (isPlaying)
            Stop();

        isPlaying = true;
        mediaControl->Run();
    }
    void Pause()
    {
        if (graphBuilder == nullptr)
            return;

        isPlaying = false;
        mediaControl->Pause();
    }
    void Stop()
    {
        if (graphBuilder == nullptr)
            return;

        isPlaying = false;
        mediaControl->Stop();
        Reset();
    }

private:
    ATL::CComPtr<IGraphBuilder> graphBuilder = nullptr;
    ATL::CComPtr<IMediaControl> mediaControl = nullptr;
    ATL::CComPtr<IMediaSeeking> mediaSeeking = nullptr;
    ATL::CComPtr<IMediaEventEx> mediaEvent = nullptr;
    bool isLoop = false;
    bool isPlaying = false;

    void Initialize()
    {
        App::Initialize();
        App::Window::AddProcedure(this);
    }
    void Reset()
    {
        LONGLONG time = 0;
        mediaSeeking->SetPositions(&time, AM_SEEKING_AbsolutePositioning, nullptr, AM_SEEKING_NoPositioning);
    }
    void OnProceed(HWND, UINT message, WPARAM, LPARAM) override
    {
        if (!isLoop)
            return;

        if (message != WM_APP)
            return;

        LONGLONG duration = 0;
        LONGLONG time = 0;
        mediaSeeking->GetDuration(&duration);
        mediaSeeking->GetPositions(&time, nullptr);
        if (duration <= time)
        {
            Stop();
            Play();
        }
    }
};