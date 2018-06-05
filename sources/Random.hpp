class Random
{
public:
    Random()
    {
        XLibraryInitialize();

        std::random_device device;
        mt.seed(device());
    }
    ~Random()
    {
    }
    void SetSeed(int seed)
    {
        mt.seed(seed);
    }
    float Get()
    {
        std::uniform_real_distribution<float> range(0.0f, 1.0f);

        return range(mt);
    }

private:
    std::mt19937 mt;
};
