class Timer
{
public:
    static float GetTime()
    {
        return Get()._time;
    }
    static float GetDeltaTime()
    {
        return Get()._deltaTime;
    }
    static int GetFrameRate()
    {
        return Get()._frameRate;
    }
    static void Update()
    {
        LARGE_INTEGER count = GetCounter();
        Get()._deltaTime = (float)(count.QuadPart - Get()._preCount.QuadPart) / Get()._frequency.QuadPart;
        Get()._preCount = GetCounter();

        Get()._time += Get()._deltaTime;

        Get()._frameCount++;
        Get()._second += Get()._deltaTime;
        if (Get()._second >= 1.0f)
        {
            Get()._frameRate = Get()._frameCount;
            Get()._frameCount = 0;
            Get()._second -= 1.0f;
        }
    }

private:
    struct Property
    {
        float _time = 0.0f;
        float _deltaTime = 0.0f;
        int _frameRate = 0;
        float _second = 0.0f;
        int _frameCount = 0;
        LARGE_INTEGER _preCount;
        LARGE_INTEGER _frequency;
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            InitializeApplication();

            Get()._preCount = GetCounter();
            Get()._frequency = GetCountFrequency();
        }

        return *prop;
    }
    static LARGE_INTEGER GetCounter()
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        return counter;
    }
    static LARGE_INTEGER GetCountFrequency()
    {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        return frequency;
    }
};