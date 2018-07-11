class Random
{
public:
    static void SetSeed(int seed)
    {
        Get().mt.seed(seed);
    }
    static float GetValue()
    {
        std::uniform_real_distribution<float> range(0.0f, 1.0f);

        return range(Get().mt);
    }
    static int Range(int min, int max)
    {
        std::uniform_int_distribution<int> range(min, max);

        return range(Get().mt);
    }
    static float Range(float min, float max)
    {
        std::uniform_real_distribution<float> range(min, max);

        return range(Get().mt);
    }

private:
    struct Property
    {
        std::mt19937 mt;
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            InitializeApplication();

            std::random_device device;
            Get().mt.seed(device());
        }

        return *prop;
    }
};
