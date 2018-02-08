class Material {
	PROTECTED Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer = nullptr;
	PROTECTED void* constant;

	PUBLIC Material() {
		char* source =
			"cbuffer Camera : register(b0) {"
			"    matrix _view;"
			"    matrix _projection;"
			"};"
			"cbuffer Object : register(b1) {"
			"    matrix _world;"
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

		Setup(source, sizeof(DirectX::XMMATRIX));
	}
	PUBLIC Material(char* source, size_t size) {
		Setup(source, size);
	}
	PUBLIC Material(wchar_t* filePath, size_t size) {
		Load(filePath, size);
	}
	PUBLIC virtual ~Material() {
	}
	PUBLIC void Load(wchar_t* filePath, size_t size) {
		std::ifstream sourceFile(filePath);
		std::istreambuf_iterator<char> iterator(sourceFile);
		std::istreambuf_iterator<char> last;
		std::string source(iterator, last);
		sourceFile.close();

		Setup(source.c_str(), size);
	}
	PUBLIC void SetConstantBuffer(void* constant) {
		this->constant = constant;
	}
	PUBLIC virtual void Attach() {
		App::GetGraphicsContext().VSSetShader(vertexShader.Get(), nullptr, 0);
		App::GetGraphicsContext().PSSetShader(pixelShader.Get(), nullptr, 0);
		App::GetGraphicsContext().IASetInputLayout(inputLayout.Get());

		if (constant != nullptr) {
			App::GetGraphicsContext().UpdateSubresource(constantBuffer.Get(), 0, nullptr, constant, 0, 0);
			App::GetGraphicsContext().VSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());
			App::GetGraphicsContext().HSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());
			App::GetGraphicsContext().DSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());
			App::GetGraphicsContext().GSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());
			App::GetGraphicsContext().PSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());
		}
	}
	PROTECTED void Setup(const char* source, size_t size) {
		Microsoft::WRL::ComPtr<ID3DBlob> vertexShaderBlob = nullptr;
		CompileShader(source, "VS", "vs_5_0", vertexShaderBlob.GetAddressOf());
		App::GetGraphicsDevice().CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, vertexShader.GetAddressOf());

		Microsoft::WRL::ComPtr<ID3DBlob> pixelShaderBlob = nullptr;
		CompileShader(source, "PS", "ps_5_0", pixelShaderBlob.GetAddressOf());
		App::GetGraphicsDevice().CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, pixelShader.GetAddressOf());

		std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc;
		inputElementDesc.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		inputElementDesc.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		inputElementDesc.push_back({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 });

		App::GetGraphicsDevice().CreateInputLayout(&inputElementDesc[0], static_cast<UINT>(inputElementDesc.size()), vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), inputLayout.GetAddressOf());

		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth = static_cast<UINT>(size);
		constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = 0;
		App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, constantBuffer.GetAddressOf());
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
