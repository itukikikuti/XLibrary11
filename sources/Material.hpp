class Material {
	PUBLIC void* cbuffer = nullptr;
	PUBLIC Texture* textures[10];
	PROTECTED Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer = nullptr;

	PUBLIC Material() {
		char* source =
			"cbuffer Object : register(b0) {"
			"    matrix _world;"
			"};"
			"cbuffer Camera : register(b1) {"
			"    matrix _view;"
			"    matrix _projection;"
			"};"
			"float4 VS(float4 vertex : POSITION) : SV_POSITION {"
			"    float4 output = vertex;"
			"    output = mul(_world, output);"
			"    output = mul(_view, output);"
			"    output = mul(_projection, output);"
			"    return output;"
			"}"
			"float4 PS(float4 position : SV_POSITION) : SV_TARGET {"
			"    return float4(1, 0, 1, 1);"
			"}";

		Setup(source);
	}
	PUBLIC Material(char* source) {
		Setup(source);
	}
	PUBLIC Material(wchar_t* filePath) {
		Load(filePath);
	}
	PUBLIC virtual ~Material() {
	}
	PUBLIC void Load(wchar_t* filePath) {
		std::ifstream sourceFile(filePath);
		std::istreambuf_iterator<char> iterator(sourceFile);
		std::istreambuf_iterator<char> last;
		std::string source(iterator, last);
		sourceFile.close();

		Setup(source.c_str());
	}
	PUBLIC virtual void Attach() {
		App::GetGraphicsContext().VSSetShader(vertexShader.Get(), nullptr, 0);
		App::GetGraphicsContext().PSSetShader(pixelShader.Get(), nullptr, 0);
		App::GetGraphicsContext().IASetInputLayout(inputLayout.Get());

		if (cbuffer != nullptr) {
			App::GetGraphicsContext().UpdateSubresource(constantBuffer.Get(), 0, nullptr, cbuffer, 0, 0);
			App::GetGraphicsContext().VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
			App::GetGraphicsContext().HSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
			App::GetGraphicsContext().DSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
			App::GetGraphicsContext().GSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
			App::GetGraphicsContext().PSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
		}

		int i = 0;
		for (Texture* texture : textures) {
			if (texture != nullptr) {
				texture->Attach(i);
			}
			i++;
		}
	}
	PUBLIC void SetCBuffer(void* cbuffer, size_t size) {
		this->cbuffer = cbuffer;

		constantBuffer.Reset();
		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth = static_cast<UINT>(size);
		constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = 0;
		App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, constantBuffer.GetAddressOf());
	}
	PUBLIC void SetTexture(int slot, Texture* texture) {
		textures[slot] = texture;
	}
	PROTECTED void Setup(const char* source) {
		vertexShader.Reset();
		Microsoft::WRL::ComPtr<ID3DBlob> vertexShaderBlob = nullptr;
		CompileShader(source, "VS", "vs_5_0", vertexShaderBlob.GetAddressOf());
		App::GetGraphicsDevice().CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, vertexShader.GetAddressOf());

		pixelShader.Reset();
		Microsoft::WRL::ComPtr<ID3DBlob> pixelShaderBlob = nullptr;
		CompileShader(source, "PS", "ps_5_0", pixelShaderBlob.GetAddressOf());
		App::GetGraphicsDevice().CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, pixelShader.GetAddressOf());

		inputLayout.Reset();
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc;
		inputElementDesc.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		inputElementDesc.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		inputElementDesc.push_back({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 });

		App::GetGraphicsDevice().CreateInputLayout(&inputElementDesc[0], static_cast<UINT>(inputElementDesc.size()), vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), inputLayout.GetAddressOf());
	}
	PROTECTED static void CompileShader(const char* source, const char* entryPoint, const char* shaderModel, ID3DBlob** out) {
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
		shaderFlags |= D3DCOMPILE_DEBUG;
#endif

		Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
		D3DCompile(source, strlen(source), nullptr, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel, shaderFlags, 0, out, &errorBlob);

		if (errorBlob != nullptr) {
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			MessageBoxA(App::GetWindowHandle(), (char*)errorBlob->GetBufferPointer(), "Shader Error", MB_OK);
		}
	}
};
