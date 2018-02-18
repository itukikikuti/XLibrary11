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

	Mesh mesh;
	Texture tex(L"assets/box.jpg");

	mesh.material.SetTexture(0, &tex);
	mesh.CreateQuad(tex.GetSize() / 2.0f);
	mesh.position = Float3(0.0f, 0.0f, 0.0f);
	mesh.Apply();

	while (App::Refresh()) {
		mesh.Draw();
	}

	return 0;
}
