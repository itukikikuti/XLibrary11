class Audio
{
public:
	Audio()
	{
		App::Initialize();

		DirectSoundCreate8(nullptr, &device, nullptr);

		device->SetCooperativeLevel(App::GetWindowHandle(), DSSCL_NORMAL);
	}
	IDirectSound8& GetDevice() const
	{
		return *device;
	}

private:
	ATL::CComPtr<IDirectSound8> device = nullptr;
};