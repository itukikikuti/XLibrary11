#define XLIBRARY_NAMESPACE_BEGIN
#define XLIBRARY_NAMESPACE_END
#include "../Library.hpp"

void PrintFrameRate()
{
    Window::SetTitle(std::to_wstring(Timer::GetFrameRate()).c_str());
    //printf("%d\n", Timer::GetFrameRate());
}
