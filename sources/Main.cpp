#include <windows.h>
#include <crtdbg.h>
#include "Graphics.h"

//int main() {
int __stdcall WinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	while (Graphics::GetInstance().Render()) {
		Sleep(10);
	}

	return 0;
}
