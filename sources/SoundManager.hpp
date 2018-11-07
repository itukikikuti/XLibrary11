/// DirectSoundのオブジェクトにアクセスできます🤔
class SoundManager
{
public:
    static IDirectSound8& GetDevice()
    {
        return *Get().device.Get();
    }

private:
    struct Property
    {
        ComPtr<IDirectSound8> device = nullptr;
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            InitializeApplication();

            DirectSoundCreate8(nullptr, &Get().device, nullptr);

            Get().device->SetCooperativeLevel(Window::GetHandle(), DSSCL_NORMAL);

            MFStartup(MF_VERSION);
        }

        return *prop;
    }
};