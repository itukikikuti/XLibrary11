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
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        Get().deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - Get().prev).count() / 1000.0f;
        Get().prev = now;

        Get().time = std::chrono::duration_cast<std::chrono::milliseconds>(now - Get().begin).count() / 1000.0f;

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
        std::chrono::high_resolution_clock::time_point begin;
        std::chrono::high_resolution_clock::time_point prev;
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            InitializeApplication();

            Get().begin = std::chrono::high_resolution_clock::now();
            Get().prev = std::chrono::high_resolution_clock::now();
        }

        return *prop;
    }
};