class Random
{
public:
    static void SetSeed(int seed)
    {
        Get()._mt.seed(seed);
    }
    static float GetValue()
    {
        std::uniform_real_distribution<float> range(0.0f, 1.0f);

        return range(Get()._mt);
    }
    static int Range(int min, int max)
    {
        std::uniform_int_distribution<int> range(min, max);

        return range(Get()._mt);
    }
    static float Range(float min, float max)
    {
        std::uniform_real_distribution<float> range(min, max);

        return range(Get()._mt);
    }

private:
    struct Property
    {
        std::mt19937 _mt;
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            InitializeApplication();

            std::random_device device;
            Get()._mt.seed(device());
        }

        return *prop;
    }
};
