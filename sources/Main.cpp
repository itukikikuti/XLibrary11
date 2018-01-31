#include "App.h"
#include "Library.h"
#include <crtdbg.h>

using namespace std;
using namespace DirectX;
using namespace GameLibrary;

int Main() {
	Library::Generate(L"GameLibrary.hpp");
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Camera camera;
	camera.position.z = -2.0f;

	Mesh mesh;

	while (App::Refresh()) {
		camera.Update();

		mesh.angles.y += App::GetDeltaTime() * 50.0f;
		mesh.Draw();
	}

	return 0;
}
