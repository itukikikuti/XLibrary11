class Proceedable {
	PUBLIC virtual void OnProceed(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) = 0;
	PUBLIC virtual ~Proceedable() {}
};
