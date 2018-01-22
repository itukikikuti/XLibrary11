struct Vertex {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 texcoord;
	DirectX::XMFLOAT3 normal;
};

class Mesh {
	PUBLIC Mesh(const wchar_t* filePath) {
		std::wifstream meshFile(filePath);
		std::wstring meshSource;

		std::vector<DirectX::XMFLOAT3> positions;
		std::vector<DirectX::XMFLOAT2> texcoords;
		std::vector<DirectX::XMFLOAT3> normals;
		std::vector<Vertex> vertices;

		while (getline(meshFile, meshSource)) {
			if (meshSource.substr(0, 2) == L"v ") {
				std::vector<std::wstring> results = SplitString(meshSource.substr(2));
				if (results.size() >= 3) {
					positions.push_back(DirectX::XMFLOAT3(std::stof(results[0]), std::stof(results[1]), std::stof(results[2])));
				}
			}
			if (meshSource.substr(0, 3) == L"vt ") {
				std::vector<std::wstring> results = SplitString(meshSource.substr(3));
				if (results.size() >= 2) {
					texcoords.push_back(DirectX::XMFLOAT2(std::stof(results[0]), std::stof(results[1])));
				}
			}
			if (meshSource.substr(0, 3) == L"vn ") {
				std::vector<std::wstring> results = SplitString(meshSource.substr(3));
				if (results.size() >= 3) {
					normals.push_back(DirectX::XMFLOAT3(std::stof(results[0]), std::stof(results[1]), std::stof(results[2])));
				}
			}
			if (meshSource.substr(0, 2) == L"f ") {
				std::vector<std::wstring> results = SplitString(std::regex_replace(meshSource.substr(2), std::wregex(LR"([a-z]|[A-Z])"), L""));
				if (results.size() >= 3) {
					for (int i = 0; i < results.size(); i++) {
						std::vector<std::wstring> tokens = SplitString(results[i], u'/');
						Vertex vertex;
						vertex.position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
						vertex.texcoord = DirectX::XMFLOAT2(0.0f, 0.0f);
						vertex.normal = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

						int index = 0;
						vertices.push_back(vertex);
					}
				}
			}
		}

		std::cout << "" << std::endl;
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
