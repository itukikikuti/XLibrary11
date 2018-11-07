/// 乱数を使えます🤔
class Random
{
public:
    /// 乱数のシードを設定します。
    static void SetSeed(int seed)
    {
        Get().mt.seed(seed);
    }
    /// 0.0から1.0の小数の乱数を取得します。
    static float GetValue()
    {
        std::uniform_real_distribution<float> range(0.0f, 1.0f);

        return range(Get().mt);
    }
    /// 整数の乱数を最小値と最大値を指定して取得します。
    static int Range(int min, int max)
    {
        std::uniform_int_distribution<int> range(min, max);

        return range(Get().mt);
    }
    /// 小数の乱数を最小値と最大値を指定して取得します。
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