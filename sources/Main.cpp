#define XLIBRARY_NAMESPACE_BEGIN
#define XLIBRARY_NAMESPACE_END
#include "App.hpp"
#include "Library.cpp"

using namespace std;
using namespace DirectX;

int MAIN()
{
    Library::Generate(L"sources/App.hpp", L"XLibrary11.hpp");

    Sprite sprite(L"assets/clock.png");
    sprite.scale = 2.0f;
    //Camera camera;
    //camera.position.y = 1.0f;
    //camera.angles.x = 10.0f;
    //Texture texture(L"assets/box.jpg");
    //Mesh mesh;
    //mesh.material.SetTexture(0, &texture);

    while (App::Refresh())
    {
        sprite.angles.z += 1.0f;
        sprite.Draw();
        //camera.Update();
        //mesh.angles.y += 1.0f;
        //mesh.Draw();
    }

    return 0;
}
