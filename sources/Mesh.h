class Mesh {
	PUBLIC Mesh(const wchar_t* filePath) {
		std::wifstream meshFile(filePath);
		std::wstring meshSource;

		int v = 0;
		int vt = 0;
		int vn = 0;
		int f = 0;
		while (getline(meshFile, meshSource)) {
			if (std::regex_match(meshSource, std::wregex(LR"(v\s.*)"))) {
				v++;
			}
			if (std::regex_match(meshSource, std::wregex(LR"(vt\s.*)"))) {
				vt++;
			}
			if (std::regex_match(meshSource, std::wregex(LR"(vn\s.*)"))) {
				vn++;
			}
			if (std::regex_match(meshSource, std::wregex(LR"(f\s.*)"))) {
				f++;
			}
		}
		std::wcout << v << std::endl;
		std::wcout << vt << std::endl;
		std::wcout << vn << std::endl;
		std::wcout << f << std::endl;
	}
};
