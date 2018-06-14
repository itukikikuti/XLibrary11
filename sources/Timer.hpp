class Timer
{
public:
    static float GetTime()
    {
        return GetInstance().time;
    }
    static float GetDeltaTime()
    {
        return GetInstance().deltaTime;
    }
    static int GetFrameRate()
    {
        return GetInstance().frameRate;
    }
    static void Update()
    {
        LARGE_INTEGER count = GetInstance().GetCounter();
        GetInstance().deltaTime = static_cast<float>(count.QuadPart - GetInstance().preCount.QuadPart) / GetInstance().frequency.QuadPart;
        GetInstance().preCount = GetInstance().GetCounter();

        GetInstance().time += GetInstance().deltaTime;

        GetInstance().frameCount++;
        GetInstance().second += GetInstance().deltaTime;
        if (GetInstance().second >= 1.0f)
        {
            GetInstance().frameRate = GetInstance().frameCount;
            GetInstance().frameCount = 0;
            GetInstance().second -= 1.0f;
        }
    }

private:
    friend std::unique_ptr<Timer>::deleter_type;

    float time = 0.0f;
    float deltaTime = 0.0f;
    int frameRate = 0;
    float second = 0.0f;
    int frameCount = 0;
    LARGE_INTEGER preCount;
    LARGE_INTEGER frequency;

    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer()
    {
        InitializeApplication();

        preCount = GetCounter();
        frequency = GetCountFrequency();
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
    LARGE_INTEGER GetCounter() const
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        return counter;
    }
    LARGE_INTEGER GetCountFrequency() const
    {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        return frequency;
    }
};