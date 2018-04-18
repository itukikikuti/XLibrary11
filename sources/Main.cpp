#define XLIBRARY_NAMESPACE_BEGIN
#define XLIBRARY_NAMESPACE_END
#include "App.hpp"
#include "Library.cpp"
#include <wrl.h>
using namespace std;
using namespace DirectX;

int MAIN()
{
    Library::Generate(L"sources/App.hpp", L"XLibrary11.hpp");

    Texture texture(L"assets/box.jpg");
    ATL::CComPtr<IDXGISurface> surface = nullptr;
    texture.GetInterface().QueryInterface(&surface);
    D2D1_BITMAP_PROPERTIES1 bitmapProperties = {};
    bitmapProperties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
    bitmapProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
    bitmapProperties.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET;
    ATL::CComPtr<ID2D1Bitmap1> bitmap = nullptr;
    App::GetGraphicsContext2D().CreateBitmapFromDxgiSurface(surface, bitmapProperties, &bitmap);
    App::GetGraphicsContext2D().SetTarget(bitmap);
    Microsoft::WRL::ComPtr<IDWriteFactory> factory = nullptr;
    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &factory);
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush = nullptr;
    App::GetGraphicsContext2D().CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), brush.GetAddressOf());
    App::GetGraphicsContext2D().SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_ALIASED);

    Camera camera;
    camera.position = Float3(0.0f, 1.0f, -5.0f);
    camera.SetPerspective(60.0f, 0.1f, 100.0f);

    Mesh mesh;
    mesh.GetMaterial().SetTexture(0, &texture);

    Text text(L"菊池いつきです");
    text.position.y = 2.0f;
    text.scale = 1.0f / 30.0f;

    Sound music(L"assets/music.mp3");
    music.SetLoop(true);
    music.SetVolume(0.5f);
    music.Play();

    Sound sound(L"assets/sound.wav");

    Sprite sprite(L"assets/clock.png");
    sprite.position.z = 100.0f;
    sprite.scale = 0.1f;

    while (App::Refresh())
    {
        camera.Update();

        App::GetGraphicsContext2D().BeginDraw();
        App::GetGraphicsContext2D().Clear(D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.0f));

        Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat = nullptr;
        factory->CreateTextFormat(L"", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fabsf(sinf(App::GetTime())) * 100.0f, L"ja-jp", textFormat.GetAddressOf());
        textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
        Microsoft::WRL::ComPtr<IDWriteTextLayout> textLayout = nullptr;
        factory->CreateTextLayout(L"菊池い\nつきです", 14, textFormat.Get(), static_cast<float>(texture.GetSize().x), static_cast<float>(texture.GetSize().y), textLayout.GetAddressOf());
        App::GetGraphicsContext2D().DrawTextLayout(D2D1::Point2F(0.0f, 0.0f), textLayout.Get(), brush.Get());
        
        App::GetGraphicsContext2D().EndDraw();

        if (App::GetKeyDown(VK_SPACE))
            sound.Play();

        text.angles.z += 1.0f;
        text.Draw();

        mesh.angles.y += 1.0f;
        mesh.Draw();

        if (App::GetKey('1'))
            App::SetMousePosition(0.0f, 0.0f);

        sprite.position.x = App::GetMousePosition().x / 5.0f;
        sprite.position.y = App::GetMousePosition().y / 5.0f;
        sprite.Draw();
    }

    return 0;
}
