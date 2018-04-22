class Sound
{
public:
    Sound()
    {
		App::Initialize();
    }
    Sound(const wchar_t* const filePath)
    {
		App::Initialize();
        Load(filePath);
    }
    virtual ~Sound()
    {
    }
	void Load(const wchar_t* const filePath)
	{
		App::GetAudioDevice();
	}

private:
};