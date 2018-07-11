class Timer
{
public:
    static float GetTime()
    {
        return Get().time;
    }
    static float GetDeltaTime()
    {
        return Get().deltaTime;
    }
    static int GetFrameRate()
    {
        return Get().frameRate;
    }
    static void Update()
    {
        LARGE_INTEGER count = GetCounter();
        Get().deltaTime = (float)(count.QuadPart - Get().preCount.QuadPart) / Get().frequency.QuadPart;
        Get().preCount = GetCounter();

        Get().time += Get().deltaTime;

        Get().frameCount++;
        Get().second += Get().deltaTime;
        if (Get().second >= 1.0f)
        {
            Get().frameRate = Get().frameCount;
            Get().frameCount = 0;
            Get().second -= 1.0f;
        }
    }

private:
    struct Property
    {
        float time = 0.0f;
        float deltaTime = 0.0f;
        int frameRate = 0;
        float second = 0.0f;
        int frameCount = 0;
        LARGE_INTEGER preCount;
        LARGE_INTEGER frequency;
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            InitializeApplication();

            Get().preCount = GetCounter();
            Get().frequency = GetCountFrequency();
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