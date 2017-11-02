#include <windows.h>
#include <crtdbg.h>
#include "Graphics.h"
#include "Sprite.h"

//int main() {
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Sprite sprite(L"box.jpg");

	int frame = 0;
	while (Graphics::GetInstance().Render()) {
		frame++;
		sprite.Draw(200.0f, 200.0f, frame, 1.0f);
		sprite.Draw(frame, frame / 2.0f, 0.0f, 0.5f);
		Sleep(10);
	}

	return 0;
}
