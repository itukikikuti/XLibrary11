class Audio
{
public:
    Audio()
    {
        XLibraryInitialize();

        DirectSoundCreate8(nullptr, &device, nullptr);

        device->SetCooperativeLevel(Window::GetHandle(), DSSCL_NORMAL);

        MFStartup(MF_VERSION);
    }
    ~Audio()
    {
        MFShutdown();
    }
    IDirectSound8& GetDevice() const
    {
        return *device;
    }

private:
    ATL::CComPtr<IDirectSound8> device = nullptr;
};