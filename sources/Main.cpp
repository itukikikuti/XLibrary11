#define XLIBRARY_NAMESPACE_BEGIN
#define XLIBRARY_NAMESPACE_END
#include "App.hpp"
#include "Library.cpp"
#include <sstream>

using namespace std;

int MAIN()
{
    Library::Generate(L"sources/App.hpp", L"XLibrary11.hpp");

    Camera camera;
    camera.position = Float3(0.0f, 1.0f, -5.0f);
    camera.SetPerspective(60.0f, 0.1f, 100.0f);
    camera.SetDepthTest(true);

    Camera uiCamera;
    uiCamera.color = Float4(1.0f, 0.0f, 1.0f, 1.0f);
    uiCamera.SetDepthTest(false);

    Texture texture(L"assets/box.jpg");

    Mesh mesh;
    mesh.CreateCube(Float3(1.0f, 0.5f, 0.3f));
    mesh.GetMaterial().SetTexture(0, &texture);

    Text text(L"あいうえおかきくけこさしすせそ\nabcdefghijklmnopqrstuvwxyz", 16.0f);
    //text.SetPivot(Float2(-1.0f, 1.0f));
    text.position.y = 2.0f;
    text.scale = 1.0f / 50.0f;

    Text number(L"0", 100.0f);
    number.position.y = 3.0f;
    number.scale = 1.0f / 100.0f;
    number.color = Float4(1.0f, 0.0f, 0.0f, 1.0f);

    Sound music(L"assets/music.mp3");
    music.SetPitch(1.0f);
    music.SetVolume(0.5f);
    music.SetPan(0.0f);
    music.SetLoop(true);
    music.Play();

    Sound sound(L"assets/sound.wav");

    Sprite sprite1(L"assets/box.jpg");
    sprite1.position.x = 1.0f;
    sprite1.scale = 1.0f / 256.0f;

    Sprite sprite(L"assets/box.jpg");

    float pos1 = -2.0f;
    float pos2 = -3.0f;
    while (App::Refresh())
    {
        camera.Update();

        music.SetPitch(Input::GetMousePosition().x / (Window::GetSize().x / 2.0f));

        if (Input::GetKeyDown('J'))
            music.Play();
        if (Input::GetKeyDown('K'))
            music.Pause();
        if (Input::GetKeyDown('L'))
            music.Stop();

        if (Input::GetKeyDown(VK_SPACE))
        {
            sound.Play();
        }

        number.angles.y += 1.0f;
        if (!Input::GetKey('2'))
        {
            text.angles.z += 1.0f;
            text.Draw();
        }
        else
        {
            wstringstream ss;
            ss << App::GetTime();
            number.Create(ss.str(), 100.0f);
        }

        number.position.x = pos1;
        number.color = Float4(1.0f, 0.0f, 0.0f, 1.0f);
        number.Draw();

        pos2 += 0.01f;
        number.position.x = pos2;
        number.color = Float4(0.0f, 0.0f, 1.0f, 1.0f);
        number.Draw();

        mesh.angles.y += 1.0f;

        mesh.position.x = 0.5f;
        mesh.Draw();

        mesh.position.x = -0.5f;
        mesh.Draw();

        if (Input::GetKey('1'))
            Input::SetMousePosition(0.0f, 0.0f);

        sprite1.angles.z = App::GetRandom() * 360.0f;
        sprite1.Draw();

        uiCamera.Update(false);

        sprite.position.x = Window::GetSize().x / 2.0f - sprite.GetSize().x / 2.0f;
        //sprite.angles.z += 10.0f;
        sprite.Draw();
    }

    return 0;
}
