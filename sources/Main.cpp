#include "App.hpp"
#include "Library.hpp"
#include <crtdbg.h>

using namespace std;
using namespace DirectX;
using namespace GameLibrary;

int Main() {
	Library::Generate(L"GameLibrary.hpp");
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Camera camera;
	Mesh mesh;
	Texture tex(L"assets/box.jpg");

	camera.position = XMFLOAT3(0.0f, 2.0f, -5.0f);
	camera.angles.x = 20.0f;
	mesh.material.SetTexture(0, &tex);

	while (App::Refresh()) {
		camera.Update();

		mesh.angles.y += App::GetDeltaTime() * 50.0f;
		mesh.Draw();
	}

	return 0;
}
