class Random
{
public:
    static void SetSeed(int seed)
    {
        GetInstance().mt.seed(seed);
    }
    static float Get()
    {
        std::uniform_real_distribution<float> range(0.0f, 1.0f);

        return range(GetInstance().mt);
    }

private:
    friend std::unique_ptr<Random>::deleter_type;

    std::mt19937 mt;

    Random(Random&) = delete;
    Random(const Random&) = delete;
    Random& operator=(Random&) = delete;
    Random& operator=(const Random&) = delete;
    Random()
    {
        InitializeApplication();

        std::random_device device;
        mt.seed(device());
    }
    ~Random()
    {
    }
    static Random& GetInstance()
    {
        static std::unique_ptr<Random> instance;

        if (instance == nullptr)
        {
            instance.reset(Instantiate());
        }

        return *instance;
    }
    static Random* Instantiate()
    {
        return new Random();
    }
};
