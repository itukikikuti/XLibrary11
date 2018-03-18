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
    camera.position.y = 1.0f;
    camera.angles.x = 10.0f;
    camera.color.x = 0.0f;

    Texture texture(L"assets/box.jpg");
    
    Mesh mesh;
    mesh.GetMaterial().SetTexture(0, &texture);

    Sprite sprite(L"assets/box.jpg");
    sprite.position.y = 1.0f;
    sprite.scale = 1.0f / sprite.GetSize().y;
    sprite.SetPivot(Float2(1.0f, -1.0f));

    while (App::Refresh())
    {
        camera.Start();

        sprite.angles.z += 1.0f;
        sprite.Draw();

        mesh.angles.y += 1.0f;
        mesh.Draw();
        
        camera.Stop();
    }

    return 0;
}
