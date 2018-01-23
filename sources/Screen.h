class Screen {
	PRIVATE const int SWAP_CHAIN_COUNT = 2;
	PRIVATE const DXGI_FORMAT SWAP_CHAIN_FORMAT = DXGI_FORMAT_R8G8B8A8_UNORM;
	PRIVATE const int MULTI_SAMPLE_COUNT = 1;
	PRIVATE const int MULTI_SAMPLE_QUALITY = 0;

	PRIVATE Microsoft::WRL::ComPtr<ID3D11Device> device = nullptr;
	PRIVATE Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain = nullptr;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11DeviceContext> context = nullptr;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader = nullptr;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader = nullptr;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout = nullptr;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTargetTexture = nullptr;

	PUBLIC Screen() {
		int createDeviceFlag = 0;
#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_DRIVER_TYPE driverTypes[] = {
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};
		int driverTypeCount = sizeof(driverTypes) / sizeof(driverTypes[0]);

		D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};
		int featureLevelCount = sizeof(featureLevels) / sizeof(featureLevels[0]);

		for (int i = 0; i < driverTypeCount; i++) {
			HRESULT result = D3D11CreateDevice(nullptr, driverTypes[i], nullptr, createDeviceFlag, featureLevels, featureLevelCount, D3D11_SDK_VERSION, device.GetAddressOf(), nullptr, nullptr);

			if (SUCCEEDED(result)) {
				break;
			}
		}

		IDXGIDevice1* dxgiDevice = nullptr;
		IDXGIAdapter* adapter = nullptr;
		IDXGIFactory* factory = nullptr;

		device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgiDevice);
		dxgiDevice->GetAdapter(&adapter);
		adapter->GetParent(__uuidof(IDXGIFactory), (void**)&factory);

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = SWAP_CHAIN_COUNT;
		swapChainDesc.BufferDesc.Width = App::GetWindowSize().x;
		swapChainDesc.BufferDesc.Height = App::GetWindowSize().y;
		swapChainDesc.BufferDesc.Format = SWAP_CHAIN_FORMAT;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		swapChainDesc.OutputWindow = App::GetWindowHandle();
		swapChainDesc.SampleDesc.Count = MULTI_SAMPLE_COUNT;
		swapChainDesc.SampleDesc.Quality = MULTI_SAMPLE_QUALITY;
		swapChainDesc.Windowed = true;

		factory->CreateSwapChain(device.Get(), &swapChainDesc, swapChain.GetAddressOf());
		factory->MakeWindowAssociation(App::GetWindowHandle(), DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER);

		factory->Release();
		adapter->Release();
		dxgiDevice->Release();

		device->GetImmediateContext(&context);

		ID3DBlob *vertexShaderBlob = nullptr;
		CompileShader(nullptr, "VS", "vs_4_0", &vertexShaderBlob);
		device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, vertexShader.GetAddressOf());
		context->VSSetShader(vertexShader.Get(), nullptr, 0);

		ID3DBlob *pixelShaderBlob = nullptr;
		CompileShader(nullptr, "PS", "ps_4_0", &pixelShaderBlob);
		device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, pixelShader.GetAddressOf());
		pixelShaderBlob->Release();
		context->PSSetShader(pixelShader.Get(), nullptr, 0);

		D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		int inputElementDescCount = sizeof(inputElementDesc) / sizeof(inputElementDesc[0]);

		device->CreateInputLayout(inputElementDesc, inputElementDescCount, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), inputLayout.GetAddressOf());
		vertexShaderBlob->Release();
		context->IASetInputLayout(inputLayout.Get());

		ID3D11BlendState* blendState = nullptr;
		D3D11_BLEND_DESC blendDesc = {};
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		device->CreateBlendState(&blendDesc, &blendState);
		context->OMSetBlendState(blendState, blendFactor, 0xffffffff);
		blendState->Release();

		swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)renderTargetTexture.GetAddressOf());
		device->CreateRenderTargetView(renderTargetTexture.Get(), nullptr, renderTargetView.GetAddressOf());
		context->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);

		D3D11_VIEWPORT viewPort = {};
		viewPort.Width = (float)App::GetWindowSize().x;
		viewPort.Height = (float)App::GetWindowSize().y;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		context->RSSetViewports(1, &viewPort);
	}
	PUBLIC ID3D11Device& GetDevice() {
		return *device.Get();
	}
	PUBLIC IDXGISwapChain& GetSwapChain() {
		return *swapChain.Get();
	}
	PUBLIC ID3D11DeviceContext& GetContext() {
		return *context.Get();
	}
	PUBLIC ID3D11RenderTargetView& GetRenderTargetView() {
		return *renderTargetView.Get();
	}
	PRIVATE void CompileShader(const wchar_t* filePath, const char* entryPoint, const char* shaderModel, ID3DBlob** out) {
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
		shaderFlags |= D3DCOMPILE_DEBUG;
#endif

		ID3DBlob *errorBlob = nullptr;

		if (filePath == nullptr) {
			char* shader = ""
				"cbuffer CB:register(b0){matrix W;matrix V;matrix P;float4 C;};"
				"Texture2D tex:register(t0);SamplerState s:register(s0);"
				"struct VO{float4 pos:SV_POSITION;float4 c:COLOR;float2 uv:TEXCOORD;};"
				"VO VS(float4 v:POSITION,float2 uv:TEXCOORD){VO o=(VO)0;o.pos=mul(W,v);o.pos=mul(V,o.pos);o.pos=mul(P,o.pos);o.c=C;o.uv=uv;return o;}"
				"float4 PS(VO o):SV_TARGET{return tex.Sample(s,o.uv)*o.c;}";

			D3DCompile(shader, strlen(shader), nullptr, nullptr, nullptr, entryPoint, shaderModel, shaderFlags, 0, out, &errorBlob);
		}
		else {
			D3DCompileFromFile(filePath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel, shaderFlags, 0, out, &errorBlob);
		}

		if (errorBlob != nullptr) {
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			MessageBoxA(App::GetWindowHandle(), (char*)errorBlob->GetBufferPointer(), "Shader Error", MB_OK);
			errorBlob->Release();
		}
	}
};
