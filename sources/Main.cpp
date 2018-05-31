#define XLIBRARY_NAMESPACE_BEGIN
#define XLIBRARY_NAMESPACE_END
#include "App.hpp"
#include "Library.cpp"
#include <sstream>

using namespace std;

int main()
{
    Library::Generate(L"sources/App.hpp", L"XLibrary11.hpp");

    Camera camera;
    camera.position = Float3(0.0f, 1.0f, -5.0f);
    camera.SetPerspective(60.0f, 0.1f, 100.0f);
    camera.SetDepthTest(true);

    Texture texture(L"assets/box.jpg");

    Mesh mesh;
    mesh.CreateCube(Float3(1.0f, 0.5f, 0.3f));
    mesh.GetMaterial().SetTexture(0, &texture);

    Text text(L"菊池いつきです。\n今日は天気も良くおならが出そうです。\n何を言ってるのかわからないですよね、僕もわからないです！\nabcdefghijklmnopqrstuvwxyz", 16.0f);
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

    Sprite sprite(L"assets/clock.png");
    sprite.position.z = 100.0f;
    sprite.scale = 0.1f;

    float pos1 = -2.0f;
    float pos2 = -3.0f;
    while (App::Refresh())
    {
        camera.Update();

        music.SetPitch(App::GetMousePosition().x / (App::GetWindowSize().x / 2.0f));

        if (App::GetKeyDown('J'))
            music.Play();
        if (App::GetKeyDown('K'))
            music.Pause();
        if (App::GetKeyDown('L'))
            music.Stop();

        if (App::GetKeyDown(VK_SPACE))
        {
            sound.Play();
        }

        number.angles.y += 1.0f;
        if (!App::GetKey('2'))
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

        if (App::GetKey('1'))
            App::SetMousePosition(0.0f, 0.0f);

        sprite1.Draw();

        sprite.position.x = App::GetMousePosition().x / 5.0f;
        sprite.position.y = App::GetMousePosition().y / 5.0f;
        sprite.Draw();
    }

    return 0;
}
