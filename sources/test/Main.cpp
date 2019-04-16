#define XLIBRARY_NAMESPACE_BEGIN
#define XLIBRARY_NAMESPACE_END
#include "../Library.hpp"
#include "../LibraryGenerator.cpp"
#include <sstream>
#include "Sub.hpp"
using namespace std;

void Type1()
{
	LibraryGenerator::Generate(L"sources/Library.hpp", L"XLibrary11.hpp");

	Sprite sprite1(L"assets/box.jpg");
	Camera camera;
	camera.position = Float3(0.0f, 1.0f, -5.0f);
	camera.SetupPerspective();
	camera.color = Float4(0.0f, 0.0f, 0.0f, 1.0f);

	Camera uiCamera;
	uiCamera.color = Float4(1.0f, 0.0f, 1.0f, 1.0f);
	uiCamera.clear = false;
	uiCamera.SetupOrthographic((float)Window::GetSize().y, true);

	Texture texture(L"assets/box.jpg");
	Texture playerTexture(L"assets/player.png");

	Mesh mesh;
	mesh.CreateCube(Float3(2.0f, 1.0f, 0.5f));
	mesh.SetTexture(&texture);

	Mesh sphere;
	sphere.CreateSphere();
	sphere.SetTexture(&playerTexture);
	sphere.position.y = 2.0f;

	Light directionalLight;
	directionalLight.type = Light::Type::Directional;
	directionalLight.angles = Float3(-50.0f, 30.0f, 0.0);
	directionalLight.intensity = 0.5f;
	directionalLight.Update();

	Light light;
	light.type = Light::Type::Point;
	light.position.z = -1.0f;
	light.color = Float4(0.0f, 1.0f, 0.0f, 0.0f);

	Light light2;
	light2.type = Light::Type::Point;
	light2.position = Float3(1.0f, 1.0f, 0.5f);
	light2.range = 2.0f;
	light2.color = Float4(1.0f, 0.0f, 0.0f, 0.0f);
	light2.intensity = 2.0f;
	light2.Update();

	Light light3;
	light3.type = Light::Type::Point;
	light3.position = Float3(-0.5f, 1.0f, -2.0f);
	light3.range = 3.0f;
	light3.color = Float4(0.0f, 0.0f, 1.0f, 0.0f);
	light3.intensity = 10.0f;
	light3.Update();

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
	text.position.x = 200.0f;
	text.position.y = 100.0f;
	text.scale = 2.0f;
	text.color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

	Sprite sprite(L"assets/box.jpg");
	sprite.scale = 0.5f;
	sprite.color.w = 0.5f;

	Sprite clock(L"assets/clock.png");
	clock.scale = 0.2f;
	clock.angles.z = -135.0f;

	float pos1 = -2.0f;
	float pos2 = -3.0f;

	while (Refresh())
	{
		camera.Update();

		PrintFrameRate();
		//printf("%d\n", Random::Range(0, 10));

		light.position.x = Input::GetMousePosition().x * 0.01f;
		light.position.y = Input::GetMousePosition().y * 0.01f;
		light.Update();

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

		if (Input::GetPadButtonDown(0, XINPUT_GAMEPAD_A))
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

		mesh.angles.z += Input::GetPadLeftThumb(0).y * 3.0f;
		mesh.angles.y += -Input::GetPadLeftThumb(0).x * 3.0f;

		mesh.position.x = 0.5f;
		mesh.angles.x = Input::GetPadRightTrigger(0) * 90.0f;
		mesh.Draw();

		mesh.position.x = -0.5f;
		mesh.angles.x = Input::GetPadLeftTrigger(0) * 90.0f;
		mesh.Draw();

		sphere.angles.x += Input::GetMouseWheel() * 0.5f;
		sphere.Draw();

		if (Input::GetKey('1'))
			Input::SetMousePosition(0.0f, 0.0f);

		sprite1.angles.z = Random::GetValue() * 360.0f;
		sprite1.Draw();

		uiCamera.Update();

		text.angles.z += Timer::GetDeltaTime() * 30.0f;
		text.Draw();

		sprite.position.x = Window::GetSize().x / 2.0f - sprite.GetSize().x * sprite.scale.x / 2.0f;
		sprite.position.y = Window::GetSize().y / 2.0f - sprite.GetSize().y * sprite.scale.y / 2.0f;
		//sprite.angles.z += 10.0f;
		sprite.Draw();

		clock.position = Input::GetMousePosition();
		clock.Draw();
	}
}

void Type2()
{
	Window::SetTitle(L"Copyright © 2019 菊池いつき All Rights Reserved.");

	int w = 1280;
	int h = 1920;
	int x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;
	SetWindowPos(Window::GetHandle(), nullptr, x, y, w, h, SWP_FRAMECHANGED);

	Camera camera;

	Mesh triangle;
	triangle.CreateCube(Float3(2.0f, 1.0f, 0.5f));

	Text title(L"DirectX11のすゝめ", 100.0f, DWRITE_TEXT_ALIGNMENT_CENTER, L"Mplus 1p");
	//Text author(L"菊池いつき", 20.0f, DWRITE_TEXT_ALIGNMENT_CENTER, L"Mplus 1p");

	while (Refresh())
	{
		camera.Update();
	}
}

int main()
{
	Type1();
	return 0;
}
