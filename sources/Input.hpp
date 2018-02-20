class Input {
	PROTECTED Float2 mousePosition;
	PROTECTED BYTE preKeyState[256];
	PROTECTED BYTE keyState[256];
	PROTECTED bool isShowCursor = true;

	PUBLIC Input() {
		Initialize();
	}
	PUBLIC ~Input() {
	}
	PROTECTED virtual void Initialize() {
		Update();
	}
	PUBLIC bool GetKey(int keyCode) const {
		return keyState[keyCode] & 0x80;
	}
	PUBLIC bool GetKeyUp(int keyCode) const {
		return !(keyState[keyCode] & 0x80) && (preKeyState[keyCode] & 0x80);
	}
	PUBLIC bool GetKeyDown(int keyCode) const {
		return (keyState[keyCode] & 0x80) && !(preKeyState[keyCode] & 0x80);
	}
	PUBLIC Float2 GetMousePosition() const {
		return mousePosition;
	}
	PUBLIC void SetMousePosition(float x, float y) {
		if (GetActiveWindow() != App::GetWindowHandle()) {
			return;
		}

		mousePosition.x = x;
		mousePosition.y = y;
		POINT point = { static_cast<int>(x), static_cast<int>(y) };
		ClientToScreen(App::GetWindowHandle(), &point);
		SetCursorPos(point.x, point.y);
	}
	PUBLIC void SetShowCursor(bool isShowCursor) {
		if (this->isShowCursor == isShowCursor) {
			return;
		}

		this->isShowCursor = isShowCursor;
		ShowCursor(isShowCursor);
	}
	PUBLIC void Update() {
		POINT point = {};
		GetCursorPos(&point);

		ScreenToClient(App::GetWindowHandle(), &point);
		mousePosition = Float2(static_cast<float>(point.x), static_cast<float>(point.y));

		for (int i = 0; i < 256; i++) {
			preKeyState[i] = keyState[i];
		}

		GetKeyboardState(keyState);
	}
};
