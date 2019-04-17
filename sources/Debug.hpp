class Debug
{
public:
	static void OpenConsole()
	{
		AllocConsole();
		FILE* fp = nullptr;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONIN$", "r", stdin);
	}
};