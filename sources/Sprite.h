// (c) 2017 Naoki Nakagawa
#pragma once
#include <wincodec.h>

namespace GameLibrary {
	class Sprite {
		PROTECTED struct Constant {
			DirectX::XMMATRIX world;
			DirectX::XMMATRIX view;
			DirectX::XMMATRIX projection;
			DirectX::XMFLOAT4 color;
		};
		PRIVATE struct Vertex {
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT2 uv;
		};

		PROTECTED DirectX::XMFLOAT2 position;
		PROTECTED float angle;
		PROTECTED DirectX::XMFLOAT2 scale;
		PROTECTED DirectX::XMFLOAT4 color;
		PROTECTED UINT width;
		PROTECTED UINT height;
		PROTECTED ID3D11Texture2D* texture;
		PROTECTED Constant constant;
		PRIVATE int indexCount;
		PRIVATE ID3D11Buffer* vertexBuffer;
		PRIVATE ID3D11Buffer* indexBuffer;
		PRIVATE ID3D11Buffer* constantBuffer;
		PRIVATE ID3D11ShaderResourceView* shaderResourceView;
		PRIVATE ID3D11SamplerState* samplerState;

		PUBLIC Sprite(const char* path) {
			CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
			IWICImagingFactory* factory = nullptr;
			CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory));
			IWICBitmapDecoder* decoder = nullptr;
			size_t length = strlen(path) + 1;
			wchar_t* wstring = new wchar_t[length];
			mbstowcs_s(nullptr, wstring, length, path, _TRUNCATE);
			factory->CreateDecoderFromFilename(wstring, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
			delete wstring;
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

			Position() = DirectX::XMFLOAT2(0.0f, 0.0f);
			Angle() = 0.0f;
			Scale() = DirectX::XMFLOAT2(1.0f, 1.0f);
			Color() = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		}
		PUBLIC virtual ~Sprite() {
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
		PUBLIC DirectX::XMINT2 GetSize() {
			return DirectX::XMINT2(width, height);
		}
		PUBLIC void SetScale(float scale) {
			Scale() = DirectX::XMFLOAT2(scale, scale);
		}
		PUBLIC DirectX::XMFLOAT2& Position() {
			return position;
		}
		PUBLIC float& Angle() {
			return angle;
		}
		PUBLIC DirectX::XMFLOAT2& Scale() {
			return scale;
		}
		PUBLIC DirectX::XMFLOAT4& Color() {
			return color;
		}
		PUBLIC void Draw() {
			constant.world = DirectX::XMMatrixIdentity();
			constant.world *= DirectX::XMMatrixScaling(width * Scale().x, height * Scale().y, 1.0f);
			constant.world *= DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(-Angle()));
			constant.world *= DirectX::XMMatrixTranslation(Position().x, -Position().y, 0.0f);
			constant.color = Color();

			Game::GetDeviceContext().UpdateSubresource(constantBuffer, 0, nullptr, &constant, 0, 0);

			Game::GetDeviceContext().VSSetConstantBuffers(0, 1, &constantBuffer);
			Game::GetDeviceContext().PSSetShaderResources(0, 1, &shaderResourceView);
			Game::GetDeviceContext().PSSetSamplers(0, 1, &samplerState);

			Game::GetDeviceContext().DrawIndexed(indexCount, 0, 0);
		}
		PROTECTED Sprite() {
		}
		PROTECTED void Initialize() {
			Vertex quad[] = {
				{ DirectX::XMFLOAT3(-0.5f, 0.5f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
				{ DirectX::XMFLOAT3(0.5f, 0.5f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
				{ DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
				{ DirectX::XMFLOAT3(0.5f, -0.5f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
			};
			int vertexCount = sizeof(quad) / sizeof(quad[0]);

			int index[] = {
				0, 1, 2,
				3, 2, 1,
			};
			indexCount = sizeof(index) / sizeof(index[0]);

			int x = Game::GetSize().x;
			int y = Game::GetSize().y;
			constant.view = DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(Game::GetSize().x / 2.0f, -Game::GetSize().y / 2.0f, 0.0f, 0.0f), DirectX::XMVectorSet(Game::GetSize().x / 2.0f, -Game::GetSize().y / 2.0f, 1.0f, 0.0f), DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
			constant.projection = DirectX::XMMatrixOrthographicLH(Game::GetSize().x * 1.0f, Game::GetSize().y * 1.0f, -1.0f, 1.0f);

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
	};
}
