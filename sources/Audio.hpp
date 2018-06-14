class Audio
{
public:
    static IDirectSound8& GetDevice()
    {
        return *GetInstance().device.Get();
    }

private:
    friend std::unique_ptr<Audio>::deleter_type;

    ComPtr<IDirectSound8> device = nullptr;

    Audio(const Audio&) = delete;
    Audio& operator=(const Audio&) = delete;
    Audio()
    {
        InitializeApplication();

        DirectSoundCreate8(nullptr, &device, nullptr);

        device->SetCooperativeLevel(Window::GetHandle(), DSSCL_NORMAL);

        MFStartup(MF_VERSION);
    }
    ~Audio()
    {
        MFShutdown();
    }
    static Audio& GetInstance()
    {
        static std::unique_ptr<Audio> instance;

        if (instance == nullptr)
        {
            instance.reset(Instantiate());
        }

        return *instance;
    }
    static Audio* Instantiate()
    {
        return new Audio();
    }
};