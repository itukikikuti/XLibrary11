// (c) 2017 Naoki Nakagawa
#pragma once
#include <wincodec.h>

namespace GameLibrary {
	class Sprite {
	public:
		Sprite() {
		}

		Sprite(wchar_t* path) {
			IWICImagingFactory* factory = nullptr;
			CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory));
			IWICBitmapDecoder* decoder = nullptr;
			factory->CreateDecoderFromFilename(path, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
			IWICBitmapFrameDecode* frame = nullptr;
			decoder->GetFrame(0, &frame);
			frame->GetSize(&width, &height);
			WICPixelFormatGUID pixelFormat;
			frame->GetPixelFormat(&pixelFormat);
			BYTE* textureBuffer = new BYTE[width * height * 4];

			if (pixelFormat != GUID_WICPixelFormat32bppRGBA) {
				IWICFormatConverter* formatConverter = nullptr;
				factory->CreateFormatConverter(&formatConverter);

				formatConverter->Initialize(frame, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);

				formatConverter->CopyPixels(0, width * 4, width * height * 4, textureBuffer);
			}
			else {
				frame->CopyPixels(0, width * 4, width * height * 4, textureBuffer);
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
			textureDesc.CPUAccessFlags = 0;
			textureDesc.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA textureSubresourceData;
			textureSubresourceData.pSysMem = textureBuffer;
			textureSubresourceData.SysMemPitch = width * 4;
			textureSubresourceData.SysMemSlicePitch = width * height * 4;
			Game::GetDevice().CreateTexture2D(&textureDesc, &textureSubresourceData, &texture);

			delete[] textureBuffer;

			Initialize();
		}

		virtual ~Sprite() {
			if (texture)
				texture->Release();

			if (shaderResourceView)
				shaderResourceView->Release();

			if (samplerState)
				samplerState->Release();

			if (vertexBuffer)
				vertexBuffer->Release();

			if (indexBuffer)
				indexBuffer->Release();

			if (constantBuffer)
				constantBuffer->Release();
		}

		DirectX::XMINT2 GetSize() {
			return DirectX::XMINT2(width, height);
		}

		void Draw(float x, float y, float angle, float scale) {
			using namespace DirectX;

			constant.world = XMMatrixIdentity();
			constant.world *= XMMatrixScaling(width * scale, height * scale, 1.0f);
			constant.world *= XMMatrixRotationZ(XMConvertToRadians(-angle));
			constant.world *= XMMatrixTranslation(x, -y, 0.0f);

			Game::GetDeviceContext().UpdateSubresource(constantBuffer, 0, nullptr, &constant, 0, 0);

			Game::GetDeviceContext().VSSetConstantBuffers(0, 1, &constantBuffer);
			Game::GetDeviceContext().PSSetShaderResources(0, 1, &shaderResourceView);
			Game::GetDeviceContext().PSSetSamplers(0, 1, &samplerState);

			Game::GetDeviceContext().DrawIndexed(indexCount, 0, 0);
		}

	protected:
		void Initialize() {
			using namespace DirectX;

			Vertex quad[] = {
				{ XMFLOAT3(-0.5f, 0.5f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
				{ XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
				{ XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
			};
			int vertexCount = sizeof(quad) / sizeof(quad[0]);

			int index[] = {
				0, 1, 2,
				3, 2, 1,
			};
			indexCount = sizeof(index) / sizeof(index[0]);

			constant.view = XMMatrixLookAtLH(XMVectorSet(Game::GetSize().x / 2.0f, -Game::GetSize().y / 2.0f, 0.0f, 0.0f), XMVectorSet(Game::GetSize().x / 2.0f, -Game::GetSize().y / 2.0f, 1.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
			constant.projection = XMMatrixOrthographicLH(Game::GetSize().x * 1.0f, Game::GetSize().y * 1.0f, -1.0f, 1.0f);

			D3D11_BUFFER_DESC vertexBufferDesc = {};
			vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertexCount;
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDesc.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
			vertexSubresourceData.pSysMem = quad;
			Game::GetDevice().CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);

			UINT stride = sizeof(Vertex);
			UINT offset = 0;
			Game::GetDeviceContext().IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
			Game::GetDeviceContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			D3D11_BUFFER_DESC indexBufferDesc = {};
			indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			indexBufferDesc.ByteWidth = sizeof(int) * indexCount;
			indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexBufferDesc.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
			indexSubresourceData.pSysMem = index;
			Game::GetDevice().CreateBuffer(&indexBufferDesc, &indexSubresourceData, &indexBuffer);

			Game::GetDeviceContext().IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

			D3D11_BUFFER_DESC constantBufferDesc = {};
			constantBufferDesc.ByteWidth = sizeof(Constant);
			constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			constantBufferDesc.CPUAccessFlags = 0;
			Game::GetDevice().CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);

			D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
			shaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderResourceViewDesc.Texture2D.MipLevels = 1;
			Game::GetDevice().CreateShaderResourceView(texture, &shaderResourceViewDesc, &shaderResourceView);

			D3D11_SAMPLER_DESC samplerDesc;
			samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.MipLODBias = 0.0f;
			samplerDesc.MaxAnisotropy = 1;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			samplerDesc.BorderColor[0] = 0;
			samplerDesc.BorderColor[1] = 0;
			samplerDesc.BorderColor[2] = 0;
			samplerDesc.BorderColor[3] = 0;
			samplerDesc.MinLOD = 0;
			samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
			Game::GetDevice().CreateSamplerState(&samplerDesc, &samplerState);
		}

		UINT width;
		UINT height;
		ID3D11Texture2D* texture;

	private:
		struct Vertex {
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT2 uv;
		};

		struct Constant {
			DirectX::XMMATRIX world;
			DirectX::XMMATRIX view;
			DirectX::XMMATRIX projection;
		};

		wchar_t* path;
		int indexCount;
		Constant constant;
		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* indexBuffer;
		ID3D11Buffer* constantBuffer;
		ID3D11ShaderResourceView* shaderResourceView;
		ID3D11SamplerState* samplerState;
	};
}
