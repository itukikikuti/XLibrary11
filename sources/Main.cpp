#include <windows.h>
#include <crtdbg.h>
#include "Graphics.h"
#include "Sprite.h"

//int main() {
int __stdcall WinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Sprite sprite;

	int frame = 0;
	while (Graphics::GetInstance().Render()) {
		frame++;
		sprite.Draw(frame, 0.0f, 0.0f, 1.0f);
		Sleep(10);
	}

	return 0;
}
