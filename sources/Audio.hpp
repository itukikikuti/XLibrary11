class Audio
{
public:
    static IDirectSound8& GetDevice()
    {
        return *Get()._device.Get();
    }

private:
    struct Property
    {
        ComPtr<IDirectSound8> _device = nullptr;
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            InitializeApplication();

            DirectSoundCreate8(nullptr, &Get()._device, nullptr);

            Get()._device->SetCooperativeLevel(Window::GetHandle(), DSSCL_NORMAL);

            MFStartup(MF_VERSION);
        }

        return *prop;
    }
};