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

    Text text(L"菊池いつきです");
    text.position.y = 2.0f;
    text.scale = 1.0f / 30.0f;

    Sound music(L"assets/music.mp3");
    music.SetLoop(true);
    music.SetVolume(0.5f);
    music.Play();

    Sound sound(L"assets/sound.wav");

    while (App::Refresh())
    {
        camera.Update();

        if (App::GetKeyDown(VK_SPACE))
            sound.Play();

        text.angles.z += 1.0f;
        text.Draw();

        mesh.angles.y += 1.0f;
        mesh.Draw();
    }

    return 0;
}
