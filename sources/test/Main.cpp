#define XLIBRARY_NAMESPACE_BEGIN
#define XLIBRARY_NAMESPACE_END
#include "../Library.hpp"
#include "../LibraryGenerator.cpp"
#include <sstream>
#include "Sub.hpp"
using namespace std;

int main()
{
    LibraryGenerator::Generate(L"sources/Library.hpp", L"XLibrary11.hpp");

    Sprite sprite1(L"assets/box.jpg");
    Camera camera;
    camera.position = Float3(0.0f, 1.0f, -5.0f);
    camera.SetupPerspective();

    Camera uiCamera;
    uiCamera.color = Float4(1.0f, 0.0f, 1.0f, 1.0f);
    uiCamera.clear = false;
    uiCamera.SetupOrthographic((float)Window::GetSize().y, true);

    Texture texture(L"assets/box.jpg");
    Texture playerTexture(L"assets/player.png");

    Mesh mesh;
    mesh.CreateCube(Float3(1.0f, 0.5f, 0.3f));
    mesh.GetMaterial().SetTexture(0, &texture);

    Mesh sphere;
    sphere.CreateSphere();
    sphere.GetMaterial().SetTexture(0, &playerTexture);
    sphere.position.y = 2.0f;

    Text number(L"0", 100.0f);
    number.position.y = 3.0f;
    number.scale = 1.0f / 100.0f;
    number.color = Float4(1.0f, 0.0f, 0.0f, 1.0f);
    number.antialias = false;

    Sound music(L"assets/music.mp3");
    music.SetPitch(1.0f);
    music.SetVolume(0.5f);
    music.SetPan(0.0f);
    music.SetLoop(true);
    music.Play();

    Sound sound(L"assets/sound.wav");

    sprite1.position.x = 1.0f;
    sprite1.scale = 1.0f / 256.0f;

    Text text(L"あいうえおかきくけこさしすせそ\nabcdefghijklmnopqrstuvwxyz", 16.0f);
    //text.SetPivot(Float2(-1.0f, 1.0f));
    text.position.y = 100.0f;
    text.scale = 2.0f;

    Sprite sprite(L"assets/box.jpg");
    sprite.scale = 0.5f;
    sprite.color.w = 0.5f;

    Sprite clock(L"assets/clock.png");

    float pos1 = -2.0f;
    float pos2 = -3.0f;
    while (Refresh())
    {
        camera.Update();

        PrintFrameRate();
        //printf("%d\n", Random::Range(0, 10));

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

        if (Input::GetKeyDown('3'))
        {
            Window::SetMode(Window::Mode::FullScreen);
        }

        number.angles.y += 1.0f;
        number.Create(std::to_wstring(Input::GetMouseWheel()), 100.0f);
        if (Input::GetKey('2'))
        {
            wstringstream ss;
            ss << Timer::GetTime();
            number.Create(ss.str(), 100.0f);
        }

        number.position.x = pos1;
        number.color = Float4(1.0f, 0.0f, 0.0f, 1.0f);
        number.Draw();

        pos2 += 0.01f;
        number.position.x = pos2;
        number.color = Float4(0.0f, 0.0f, 1.0f, 1.0f);
        number.Draw();

        mesh.angles.y += 30.0f * Timer::GetDeltaTime();

        mesh.position.x = 0.5f;
        mesh.Draw();

        mesh.position.x = -0.5f;
        mesh.Draw();

        sphere.angles.x += Input::GetMouseWheel() * 0.5f;
        sphere.Draw();

        if (Input::GetKey('1'))
            Input::SetMousePosition(0.0f, 0.0f);

        sprite1.angles.z = Random::GetValue() * 360.0f;
        sprite1.Draw();

        uiCamera.Update();

        text.angles.z += 1.0f;
        text.Draw();

        sprite.position.x = Window::GetSize().x / 2.0f - sprite.GetSize().x * sprite.scale.x / 2.0f;
        sprite.position.y = Window::GetSize().y / 2.0f - sprite.GetSize().y * sprite.scale.y / 2.0f;
        //sprite.angles.z += 10.0f;
        sprite.Draw();

        clock.position = Input::GetMousePosition();
        clock.Draw();
    }

    return 0;
}
