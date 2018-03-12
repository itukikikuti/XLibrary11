#define XLIBRARY_NAMESPACE_BEGIN
#define XLIBRARY_NAMESPACE_END
#include "App.hpp"
#include "Library.cpp"

using namespace std;
using namespace DirectX;

int MAIN()
{
    Library::Generate(L"sources/App.hpp", L"XLibrary11.hpp");

    Sprite sprite(L"assets/box.jpg");

    while (App::Refresh())
    {
        sprite.angles.z += 1.0f;
        sprite.Draw();
    }

    return 0;
}
