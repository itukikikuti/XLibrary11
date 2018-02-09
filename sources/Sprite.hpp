class Sprite {
	PROTECTED struct ConstantBuffer {
		DirectX::XMMATRIX world;
		Float4 color;
	};

	PUBLIC Float3 position;
	PUBLIC Float3 angles;
	PUBLIC Float3 scale;
	PUBLIC Float4 color;
	PROTECTED UINT width;
	PROTECTED UINT height;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	PROTECTED ConstantBuffer cbuffer;
	PRIVATE int indexCount;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;

	PUBLIC Sprite() {
		Initialize();
	}
	PUBLIC Sprite(const wchar_t* filePath) {
		CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

		Microsoft::WRL::ComPtr<IWICImagingFactory> factory = nullptr;
		CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(factory.GetAddressOf()));

		Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder = nullptr;
		BYTE* textureBuffer = nullptr;

		if (SUCCEEDED(factory->CreateDecoderFromFilename(filePath, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, decoder.GetAddressOf()))) {
			Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame = nullptr;
			decoder->GetFrame(0, frame.GetAddressOf());
			frame->GetSize(&width, &height);

			WICPixelFormatGUID pixelFormat;
			frame->GetPixelFormat(&pixelFormat);
			textureBuffer = new BYTE[width * height * 4];

			if (pixelFormat != GUID_WICPixelFormat32bppRGBA) {
				Microsoft::WRL::ComPtr<IWICFormatConverter> formatConverter = nullptr;
				factory->CreateFormatConverter(formatConverter.GetAddressOf());

				formatConverter->Initialize(frame.Get(), GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);

				formatConverter->CopyPixels(0, width * 4, width * height * 4, textureBuffer);
			}
			else {
				frame->CopyPixels(0, width * 4, width * height * 4, textureBuffer);
			}
		}
		else {
			width = height = 100;
			textureBuffer = new BYTE[width * height * 4];
			for (UINT y = 0; y < height; y++) {
				for (UINT x = 0; x < width; x++) {
					BYTE color[4] = { 0xff, 0x00, 0xff, 0xff };
					memcpy(&textureBuffer[x * 4 + y * (width * 4)], color, sizeof(DWORD));
				}
			}
		}

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		textureDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA textureSubresourceData;
		textureSubresourceData.pSysMem = textureBuffer;
		textureSubresourceData.SysMemPitch = width * 4;
		textureSubresourceData.SysMemSlicePitch = width * height * 4;
		App::GetGraphicsDevice().CreateTexture2D(&textureDesc, &textureSubresourceData, texture.GetAddressOf());

		delete[] textureBuffer;

		Initialize();
	}
	PUBLIC virtual ~Sprite() {
	}
	PUBLIC DirectX::XMINT2 GetSize() {
		return DirectX::XMINT2(width, height);
	}
	PUBLIC void Draw() {
		cbuffer.world = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) * DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(angles.x), DirectX::XMConvertToRadians(angles.y), DirectX::XMConvertToRadians(angles.z))* DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		cbuffer.color = color;
		App::GetGraphicsContext().UpdateSubresource(constantBuffer.Get(), 0, nullptr, &cbuffer, 0, 0);
		App::GetGraphicsContext().VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().PSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());

		App::GetGraphicsContext().PSSetShaderResources(0, 1, shaderResourceView.GetAddressOf());
		App::GetGraphicsContext().PSSetSamplers(0, 1, samplerState.GetAddressOf());

		App::GetGraphicsContext().DrawIndexed(indexCount, 0, 0);
	}
	PROTECTED void Initialize() {
		position = Float3(0.0f, 0.0f, 0.0f);
		angles = Float3(0.0f, 0.0f, 0.0f);
		scale = Float3(1.0f, 1.0f, 1.0f);
		color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

		Vertex quad[] = {
			{ Float3(-0.5f, 0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(0.0f, 0.0f) },
			{ Float3(0.5f, 0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(1.0f, 0.0f) },
			{ Float3(-0.5f, -0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(0.0f, 1.0f) },
			{ Float3(0.5f, -0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(1.0f, 1.0f) },
		};
		int vertexCount = sizeof(quad) / sizeof(quad[0]);

		int index[] = {
			0, 1, 2,
			3, 2, 1,
		};
		indexCount = sizeof(index) / sizeof(index[0]);

		int x = App::GetWindowSize().x;
		int y = App::GetWindowSize().y;

		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
		vertexSubresourceData.pSysMem = quad;
		App::GetGraphicsDevice().CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, vertexBuffer.GetAddressOf());

		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		App::GetGraphicsContext().IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
		App::GetGraphicsContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(int) * indexCount;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
		indexSubresourceData.pSysMem = index;
		App::GetGraphicsDevice().CreateBuffer(&indexBufferDesc, &indexSubresourceData, indexBuffer.GetAddressOf());

		App::GetGraphicsContext().IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
		constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = 0;
		App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, constantBuffer.GetAddressOf());

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
		shaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;
		App::GetGraphicsDevice().CreateShaderResourceView(texture.Get(), &shaderResourceViewDesc, shaderResourceView.GetAddressOf());

		D3D11_SAMPLER_DESC samplerDesc;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.BorderColor[0] = 0.0f;
		samplerDesc.BorderColor[1] = 0.0f;
		samplerDesc.BorderColor[2] = 0.0f;
		samplerDesc.BorderColor[3] = 0.0f;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		App::GetGraphicsDevice().CreateSamplerState(&samplerDesc, samplerState.GetAddressOf());
	}
};
