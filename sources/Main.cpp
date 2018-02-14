#define XLIBRARY_NAMESPACE_BEGIN
#define XLIBRARY_NAMESPACE_END
#include "App.hpp"
#include "Library.cpp"
#include <crtdbg.h>

using namespace std;
using namespace DirectX;

int Main() {
	Library::Generate(L"sources/App.hpp", L"XLibrary11.hpp");
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Camera camera;
	Mesh mesh;
	Texture tex(L"assets/box.jpg");

	camera.position = Float3(0.0f, 1.0f, -2.0f);
	camera.angles.x = 20.0f;
	mesh.CreateCube();
	mesh.Apply();
	mesh.material.SetTexture(0, &tex);
	
	while (App::Refresh()) {
		camera.Update();

		mesh.angles.y += App::GetDeltaTime() * 50.0f;

		mesh.position = Float3(0.5f, 0.0f, 0.0f);
		mesh.Draw();

		mesh.position = Float3(-0.5f, 0.0f, 0.0f);
		mesh.Draw();
	}

	return 0;
}
