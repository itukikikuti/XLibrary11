class Window
{
	PUBLIC class Proceedable
	{
		PUBLIC virtual void OnProceed(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) = 0;
	};

	PROTECTED HWND handle;
	PROTECTED const DWORD style = WS_OVERLAPPEDWINDOW;

	PUBLIC Window()
	{
		App::Initialize();
		Initialize();
	}
	PUBLIC ~Window()
	{
		UnregisterClassW(App::NAME, GetModuleHandleW(nullptr));
	}
	PROTECTED virtual void Initialize()
	{
		HINSTANCE instance = GetModuleHandleW(nullptr);

		WNDCLASSEXW windowClass = {};
		windowClass.cbSize = sizeof(WNDCLASSEXW);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = ProceedMessage;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = instance;
		windowClass.hIcon = nullptr;
		windowClass.hCursor = (HCURSOR)LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
		windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		windowClass.lpszMenuName = nullptr;
		windowClass.lpszClassName = App::NAME;
		windowClass.hIconSm = nullptr;
		RegisterClassExW(&windowClass);

		handle = CreateWindowW(App::NAME, App::NAME, style, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, nullptr, nullptr, instance, nullptr);

		SetSize(1280.0f, 720.0f);
		ShowWindow(handle, SW_SHOWNORMAL);
	}
	PUBLIC HWND GetHandle() const
	{
		return handle;
	}
	PUBLIC DirectX::XMINT2 GetSize() const
	{
		RECT clientRect = {};
		GetClientRect(handle, &clientRect);

		return DirectX::XMINT2(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
	}
	PUBLIC void SetSize(int width, int height)
	{
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
	PUBLIC wchar_t* const GetTitle() const
	{
		wchar_t* title = nullptr;
		GetWindowTextW(handle, title, GetWindowTextLengthW(handle));
		return title;
	}
	PUBLIC void SetTitle(const wchar_t* const title)
	{
		SetWindowTextW(handle, title);
	}
	PUBLIC void SetFullScreen(bool isFullScreen)
	{
		static DirectX::XMINT2 size = GetSize();

		if (isFullScreen)
		{
			size = GetSize();
			int w = GetSystemMetrics(SM_CXSCREEN);
			int h = GetSystemMetrics(SM_CYSCREEN);
			SetWindowLongPtrW(handle, GWL_STYLE, WS_VISIBLE | WS_POPUP);
			SetWindowPos(handle, HWND_TOP, 0, 0, w, h, SWP_FRAMECHANGED);
		}
		else
		{
			SetWindowLongPtrW(handle, GWL_STYLE, WS_VISIBLE | style);
			SetWindowPos(handle, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
			SetSize(size.x, size.y);
		}
	}
	PUBLIC void AddProcedure(Proceedable* const procedure)
	{
		GetProcedures().push_front(procedure);
	}
	PUBLIC void RemoveProcedure(Proceedable* const procedure)
	{
		GetProcedures().remove(procedure);
	}
	PUBLIC bool Update()
	{
		MSG message = {};
		
		while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
				return false;

			TranslateMessage(&message);
			DispatchMessageW(&message);
		}

		return true;
	}
	PROTECTED static std::forward_list<Proceedable*>& GetProcedures()
	{
		static std::forward_list<Proceedable*> procedures;
		return procedures;
	}
	PROTECTED static LRESULT CALLBACK ProceedMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
	{
		for (Proceedable* procedure : GetProcedures())
		{
			procedure->OnProceed(window, message, wParam, lParam);
		}

		if (message == WM_DESTROY)
			PostQuitMessage(0);

		return DefWindowProcW(window, message, wParam, lParam);
	}
};
