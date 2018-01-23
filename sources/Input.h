class Input {
	PRIVATE DirectX::XMINT2 mousePosition;
	PRIVATE BYTE preKeyState[256];
	PRIVATE BYTE keyState[256];

	PUBLIC Input() {
		Update();
	}
	PUBLIC DirectX::XMINT2 GetMousePosition() {
		return mousePosition;
	}
	PUBLIC bool GetKey(int keyCode) {
		return keyState[keyCode] & 0x80;
	}
	PUBLIC bool GetKeyUp(int keyCode) {
		return !(keyState[keyCode] & 0x80) && (preKeyState[keyCode] & 0x80);
	}
	PUBLIC bool GetKeyDown(int keyCode) {
		return (keyState[keyCode] & 0x80) && !(preKeyState[keyCode] & 0x80);
	}
	PUBLIC void Update() {
		POINT point = {};
		GetCursorPos(&point);

		ScreenToClient(App::GetWindowHandle(), &point);
		mousePosition = DirectX::XMINT2(point.x, point.y);

		for (int i = 0; i < 256; i++) {
			preKeyState[i] = keyState[i];
		}

		GetKeyboardState(keyState);
	}
};
