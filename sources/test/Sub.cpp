#define XLIBRARY_NAMESPACE_BEGIN
#define XLIBRARY_NAMESPACE_END
#include "../Library.hpp"

void PrintFrameRate()
{
    printf("%d\n", Timer::GetFrameRate());
}
