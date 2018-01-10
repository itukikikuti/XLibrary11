class Mesh {
	PUBLIC Mesh(const wchar_t* filePath) {
		std::wifstream meshFile(filePath);
		std::wstring meshSource;

		std::vector<XMFLOAT3> vertices;
		std::vector<XMFLOAT2> texcoords;
		std::vector<XMFLOAT3> normals;

		while (getline(meshFile, meshSource)) {
			if (meshSource.substr(0, 2) == L"v ") {
				std::vector<std::wstring> results = SplitString(meshSource.substr(2));
				if (results.size() >= 3) {
					vertices.push_back(XMFLOAT3(std::stod(results[0]), std::stod(results[1]), std::stod(results[2])));
				}
			}
			if (meshSource.substr(0, 3) == L"vt ") {
				std::vector<std::wstring> results = SplitString(meshSource.substr(3));
				if (results.size() >= 2) {
					texcoords.push_back(XMFLOAT2(std::stod(results[0]), std::stod(results[1]), std::stod(results[2])));
				}
			}
			if (meshSource.substr(0, 2) == L"v ") {
				std::vector<std::wstring> results = SplitString(meshSource.substr(2));
				if (results.size() >= 3) {
					normals.push_back(XMFLOAT3(std::stod(results[0]), std::stod(results[1]), std::stod(results[2])));
				}
			}
		}
	}
	PRIVATE std::vector<std::wstring> SplitString(const std::wstring &str, wchar_t delimiter = u' ') {
		std::vector<std::wstring> results;
		std::wstring temp;
		for (wchar_t character : str) {
			if (character == delimiter) {
				results.push_back(temp);
				temp.clear();
			}
			else {
				temp += character;
			}
		}
		results.push_back(temp);
		return results;
	}
};
