class Timer
{
public:
    static float GetTime()
    {
        return GetInstance()._time;
    }
    static float GetDeltaTime()
    {
        return GetInstance()._deltaTime;
    }
    static int GetFrameRate()
    {
        return GetInstance()._frameRate;
    }
    static void Update()
    {
        LARGE_INTEGER count = GetInstance().GetCounter();
        GetInstance()._deltaTime = (float)(count.QuadPart - GetInstance()._preCount.QuadPart) / GetInstance()._frequency.QuadPart;
        GetInstance()._preCount = GetInstance().GetCounter();

        GetInstance()._time += GetInstance()._deltaTime;

        GetInstance()._frameCount++;
        GetInstance()._second += GetInstance()._deltaTime;
        if (GetInstance()._second >= 1.0f)
        {
            GetInstance()._frameRate = GetInstance()._frameCount;
            GetInstance()._frameCount = 0;
            GetInstance()._second -= 1.0f;
        }
    }

private:
    friend std::unique_ptr<Timer>::deleter_type;

    float _time = 0.0f;
    float _deltaTime = 0.0f;
    int _frameRate = 0;
    float _second = 0.0f;
    int _frameCount = 0;
    LARGE_INTEGER _preCount;
    LARGE_INTEGER _frequency;

    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer()
    {
        InitializeApplication();

        _preCount = GetCounter();
        _frequency = GetCountFrequency();
    }
    ~Timer()
    {
    }
    static Timer& GetInstance()
    {
        static std::unique_ptr<Timer> instance;

        if (instance == nullptr)
        {
            instance.reset(Instantiate());
        }

        return *instance;
    }
    static Timer* Instantiate()
    {
        return new Timer();
    }
    LARGE_INTEGER GetCounter()
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        return counter;
    }
    LARGE_INTEGER GetCountFrequency()
    {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        return frequency;
    }
};