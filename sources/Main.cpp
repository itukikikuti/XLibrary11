#include "App.h"
#include <fstream>
#include <codecvt>
#include <string>
#include <regex>
#include <crtdbg.h>

using namespace std;
using namespace DirectX;
using namespace GameLibrary;

wstring GetSourceCode(const wchar_t* filePath) {
	wifstream sourceFile(filePath);
	if (sourceFile.fail()) {
		wstring empty = L"";
		return empty;
	}
	sourceFile.imbue(locale(locale(""), new codecvt_utf8_utf16<wchar_t, 0x10ffff, consume_header>()));
	istreambuf_iterator<wchar_t> iterator(sourceFile);
	istreambuf_iterator<wchar_t> last;
	wstring sourceCode(iterator, last);
	sourceFile.close();
	return sourceCode;
}
void MargeSourceCode(const wchar_t* fileName, wstring& sourceCode) {
	wstring from = L"#include \"" + wstring(fileName) + L"\"";
	wstring filePath = L"sources/" + wstring(fileName);

	wstring::size_type pos = sourceCode.find(from);
	sourceCode.replace(pos, from.size(), GetSourceCode(filePath.c_str()));
}
void LinkLibrary() {
	wstring library = GetSourceCode(L"sources/App.h");

	MargeSourceCode(L"Window.h", library);
	MargeSourceCode(L"Graphic.h", library);
	MargeSourceCode(L"Input.h", library);
	MargeSourceCode(L"Time.h", library);
	MargeSourceCode(L"Camera.h", library);
	MargeSourceCode(L"Mesh.h", library);
	MargeSourceCode(L"Sprite.h", library);
	MargeSourceCode(L"Text.h", library);

	wofstream libraryFile(L"GameLibrary.h");
	libraryFile.imbue(locale(locale(""), new codecvt_utf8_utf16<wchar_t, 0x10ffff, generate_header>()));
	libraryFile << library;
	libraryFile.close();
}

int Main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	LinkLibrary();
	Camera camera;
	Sprite sprite(L"assets/4.JPG");

	camera.position.z = -1.0f;

	while (App::Refresh()) {
		camera.Update();

		sprite.angles.y += App::GetDeltaTime() * 10.0f;
		sprite.Draw();
	}

	return 0;
}
