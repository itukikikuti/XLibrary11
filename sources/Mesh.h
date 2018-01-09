class Mesh {
	PUBLIC Mesh(const wchar_t* filePath) {
		std::wifstream meshFile(filePath);
		std::wstring meshSource;

		while (getline(meshFile, meshSource)) {
			std::wcout << meshSource << std::endl;
		}
	}
};
