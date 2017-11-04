#include <crtdbg.h>
#include "Game.h"
#include "Sprite.h"

using namespace GameLibrary;

//int main() {
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Sprite sprite1(L"box.jpg");
	Sprite sprite2(L"PATAPON.png");

	float t = 0.0f;
	while (Game::Update()) {
		t += Game::GetDeltaTime();

		sprite1.Draw(200.0f, 200.0f, t * 360.0f, 1.0f);
		sprite2.Draw(t * 50.0f, t * 25.0f, 0.0f, 0.5f);
	}

	return 0;
}
