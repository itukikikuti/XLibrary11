#include <fstream>
#include <string>
#include <regex>
#include <crtdbg.h>
#include "Game.h"

using namespace std;
using namespace DirectX;
using namespace GameLibrary;

string GetSourceCode(const char* path) {
	ifstream sourceFile(path);
	istreambuf_iterator<char> iterator(sourceFile);
	istreambuf_iterator<char> last;
	string sourceCode(iterator, last);
	sourceFile.close();
	return sourceCode;
}

void MargeSourceCode(const char* file, string& sourceCode) {
	string from = "#include \"" + string(file) + "\"";
	string path = "sources/" + string(file);

	string::size_type pos = sourceCode.find(from);
	sourceCode.replace(pos, from.size(), GetSourceCode(path.c_str()));
}

void LinkLibrary() {
	string game = GetSourceCode("sources/Game.h");

	MargeSourceCode("Sprite.h", game);
	MargeSourceCode("Text.h", game);

	ofstream libraryFile("GameLibrary.h");
	libraryFile << game;
	libraryFile.close();
}

int Main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	LinkLibrary();

	Sprite sprite1(_T("clock.png"));
	sprite1.Position() = XMFLOAT2(200.0f, 200.0f);
	Sprite sprite2(_T("4.JPG"));
	sprite2.Position() = XMFLOAT2(1000.0f, 250.0f);

	Game::AddFont(_T("衡山毛筆フォント行書.ttf"));
	Game::SetTitle(_T("くぁwせdrftgyふじこlp"));

	Text text1(_T("あ"));
	text1.SetScale(0.5f);
	Text text2(_T("あ"));
	Text text3(_T("玉"), _T("衡山毛筆フォント行書"));

	float t = 0.0f;
	while (Game::Update()) {
		t += Game::GetDeltaTime();

		sprite1.Angle() = t * (360.0f);
		sprite1.Scale().y = 1.3f;
		sprite1.Draw();
		sprite1.Angle() = t * (360.0f / 60.0f);
		sprite1.Scale().y = 1.0f;
		sprite1.Draw();
		sprite1.Angle() = t * (360.0f / 60.0f / 12.0f);
		sprite1.Scale().y = 0.7f;
		sprite1.Draw();

		sprite2.Draw();

		if (Game::GetKey(VK_LBUTTON)) {
			text1.Position() = XMFLOAT2(Game::GetMousePosition().x, Game::GetMousePosition().y);
		}
		text1.Angle() = Game::GetTime() * -100.0f;
		text1.Draw();

		text2.Position() = XMFLOAT2(Game::GetSize().x / 2.0f, Game::GetSize().y / 2.0f - 200.0f);
		text2.Draw();

		text3.Position() = XMFLOAT2(Game::GetSize().x / 2.0f, Game::GetSize().y / 2.0f + 200.0f);
		text3.SetScale(2.0f + sinf(t) * 1.0f);
		text3.Draw();
	}

	return 0;
}
