#define XLIBRARY_NAMESPACE_BEGIN
#define XLIBRARY_NAMESPACE_END
#include "App.hpp"
#include "Library.cpp"

using namespace std;
using namespace DirectX;

int MAIN()
{
    Library::Generate(L"sources/App.hpp", L"XLibrary11.hpp");

    Camera camera;
    camera.position = Float3(0.0f, 1.0f, -5.0f);
    camera.SetPerspective(60.0f, 0.1f, 100.0f);

    Mesh mesh;
    Texture texture(L"assets/box.jpg");

    mesh.GetMaterial().SetTexture(0, &texture);

    while (App::Refresh())
    {
        camera.Update();

        mesh.angles.y += 1.0f;
        mesh.Draw();
    }

    return 0;
}
