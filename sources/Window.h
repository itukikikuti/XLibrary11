class Window {
	PRIVATE HWND handle;
	PRIVATE const DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_SIZEBOX;

	PUBLIC Window() {
		HINSTANCE instance = GetModuleHandleW(nullptr);

		WNDCLASSEXW windowClass = {};
		windowClass.cbSize = sizeof(WNDCLASSEXW);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = Process;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = instance;
		windowClass.hIcon = nullptr;
		windowClass.hCursor = (HCURSOR)LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
		windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		windowClass.lpszMenuName = nullptr;
		windowClass.lpszClassName = L"GameLibrary";
		windowClass.hIconSm = nullptr;
		RegisterClassExW(&windowClass);

		handle = CreateWindowW(L"GameLibrary", L"GameLibrary", style, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, nullptr, nullptr, instance, nullptr);

		SetSize(1280, 720);

		ShowWindow(handle, SW_SHOWNORMAL);
	}
	PUBLIC HWND GetHandle() {
		return handle;
	}
	PUBLIC DirectX::XMINT2 GetSize() {
		RECT clientRect = {};
		GetClientRect(handle, &clientRect);

		return DirectX::XMINT2(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
	}
	PUBLIC void SetSize(int width, int height) {
		RECT windowRect = {};
		RECT clientRect = {};
		GetWindowRect(handle, &windowRect);
		GetClientRect(handle, &clientRect);

		int w = (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left) + width;
		int h = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top) + height;

		int x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
		int y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;

		SetWindowPos(handle, nullptr, x, y, w, h, SWP_FRAMECHANGED);
	}
	PUBLIC wchar_t* GetTitle() {
		wchar_t* title = nullptr;
		GetWindowTextW(handle, title, GetWindowTextLengthW(handle));
		return title;
	}
	PUBLIC void SetTitle(const wchar_t* title) {
		SetWindowTextW(handle, title);
	}
	PUBLIC void SetFullScreen(bool isFullscreen) {
		static DirectX::XMINT2 size = GetSize();

		if (isFullscreen) {
			size = GetSize();
			int w = GetSystemMetrics(SM_CXSCREEN);
			int h = GetSystemMetrics(SM_CYSCREEN);
			SetWindowLongPtrW(handle, GWL_STYLE, WS_VISIBLE | WS_POPUP);
			SetWindowPos(handle, HWND_TOP, 0, 0, w, h, SWP_FRAMECHANGED);
		}
		else {
			SetWindowLongPtrW(handle, GWL_STYLE, WS_VISIBLE | style);
			SetWindowPos(handle, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
			SetSize(size.x, size.y);
		}
	}
	PRIVATE static LRESULT WINAPI Process(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
		switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProcW(window, message, wParam, lParam);
		}
		return 0;
	}
};
