#include <windows.h>
#include <crtdbg.h>
#include "Graphics.h"
#include "Sprite.h"

//int main() {
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Sprite sprite1(L"box.jpg");
	Sprite sprite2(L"PATAPON.png");
	Graphics::GetDeviceContext();

	float t = 0.0f;
	while (Graphics::Update()) {
		t += Graphics::GetDeltaTime() * 360.0f;

		sprite2.Draw(200.0f, 200.0f, t, 1.0f);
		sprite1.Draw(t, t / 2.0f, 0.0f, 0.5f);
	}

	return 0;
}
