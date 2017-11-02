#include <windows.h>
#include <crtdbg.h>
#include <memory>
#include "Graphics.h"

//int main() {
int __stdcall WinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::unique_ptr<Graphics> graphics(new Graphics());
	while (graphics->Render()) {
		Sleep(10);
	}

	return 0;
}
