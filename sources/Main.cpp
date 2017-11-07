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

void MargeSourceCode(char* file, string& sourceCode) {
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

//int main() {
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	LinkLibrary();

	Game::AddFont("衡山毛筆フォント行書.ttf");
	Game::SetTitle("くぁwせdrftgyふじこlp");

	Sprite sprite1(L"clock.png");
	Sprite sprite2(L"4.JPG");
	Text text1("あ");
	Text text2("王", "衡山毛筆フォント行書");

	float t = 0.0f;
	XMINT2 position(0, 0);
	while (Game::Update()) {
		t += Game::GetDeltaTime();

		sprite1.Draw(200.0f, 200.0f, t * (360.0f), 1.3f);
		sprite1.Draw(200.0f, 200.0f, t * (360.0f / 60.0f), 1.0f);
		sprite1.Draw(200.0f, 200.0f, t * (360.0f / 60.0f / 12.0f), 0.7f);

		sprite2.Draw(1000.0f, 250.0f, 0.0f, 1.0f);

		if (Game::GetKeyUp(VK_LBUTTON)) {
			position = XMINT2(Game::GetMousePosition().x, Game::GetMousePosition().y);
		}
		text1.Draw(position.x, position.y, t * -2000.0f, 0.5f);;

		text1.Draw(Game::GetSize().x / 2.0f, Game::GetSize().y / 2.0f - 200.0f, 0.0f, 1.0f);
		text2.Draw(Game::GetSize().x / 2.0f, Game::GetSize().y / 2.0f + 200.0f, 0.0f, 2.0f + sinf(t) * 1.0f);
	}

	return 0;
}
