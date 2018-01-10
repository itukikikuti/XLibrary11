class Mesh {
	PUBLIC Mesh(const wchar_t* filePath) {
		std::wifstream meshFile(filePath);
		std::wstring meshSource;

		std::vector<XMFLOAT3> vertices;

		while (getline(meshFile, meshSource)) {
			if (meshSource.substr(0, 2) == L"v ") {
				std::vector<std::wstring> results = SplitString(meshSource.substr(2));
				if (results.size() >= 3) {
					vertices.push_back(XMFLOAT3(std::stod(results[0]), std::stod(results[1]), std::stod(results[2])));
				}
			}
		}

		std::wcout << L"a";
	}
	PRIVATE std::vector<std::wstring> SplitString(const std::wstring &str, wchar_t delimiter = u' ') {
		std::vector<std::wstring> results;
		std::wstring temp;
		for (wchar_t character : str) {
			if (character == delimiter) {
				if (!temp.empty()) {
					results.push_back(temp);
				}
				temp.clear();
			}
			else {
				temp += character;
			}
		}
		if (!temp.empty()) {
			results.push_back(temp);
		}
		return results;
	}
};
