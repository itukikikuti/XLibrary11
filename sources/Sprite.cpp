// (c) 2017 Naoki Nakagawa
#include <d3d11.h>
#include <DirectXMath.h>
#include "Graphics.h"
#include "Sprite.h"

using namespace std;
using namespace DirectX;

Sprite::Sprite() {
	HRESULT result = {};

	Vertex quad[] = {
		{ XMFLOAT3(-0.5f, 0.5f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
	};
	vertexCount = sizeof(quad) / sizeof(quad[0]);

	int index[] = {
		0, 1, 2,
		3, 2, 1,
	};
	indexCount = sizeof(index) / sizeof(index[0]);

	constant.view = XMMatrixLookAtLH(XMVectorSet(Graphics::CLIENT_WIDTH / 2.0f, -Graphics::CLIENT_HEIGHT / 2.0f, 0.0f, 0.0f), XMVectorSet(Graphics::CLIENT_WIDTH / 2.0f, -Graphics::CLIENT_HEIGHT / 2.0f, 1.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	constant.projection = XMMatrixOrthographicLH(Graphics::CLIENT_WIDTH * 1.0f, Graphics::CLIENT_HEIGHT * 1.0f, -1.0f, 1.0f);

	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
	vertexSubresourceData.pSysMem = quad;
	result = Graphics::GetInstance().GetDevice().CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);

	if (FAILED(result)) {
		throw bad_alloc();
	}
	else {
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		Graphics::GetInstance().GetDeviceContext().IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		Graphics::GetInstance().GetDeviceContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(int) * indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
	indexSubresourceData.pSysMem = index;
	result = Graphics::GetInstance().GetDevice().CreateBuffer(&indexBufferDesc, &indexSubresourceData, &indexBuffer);

	if (FAILED(result)) {
		throw bad_alloc();
	}
	else {
		Graphics::GetInstance().GetDeviceContext().IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.ByteWidth = sizeof(Constant);
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	result = Graphics::GetInstance().GetDevice().CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);

	if (FAILED(result)) {
		throw bad_alloc();
	}
	else {
		Graphics::GetInstance().GetDeviceContext().VSSetConstantBuffers(0, 1, &constantBuffer);
		Graphics::GetInstance().GetDeviceContext().GSSetConstantBuffers(0, 1, &constantBuffer);
		Graphics::GetInstance().GetDeviceContext().PSSetConstantBuffers(0, 1, &constantBuffer);
	}
}

Sprite::~Sprite() {
	if (vertexBuffer)
		vertexBuffer->Release();

	if (indexBuffer)
		indexBuffer->Release();

	if (constantBuffer)
		constantBuffer->Release();
}

void Sprite::Draw(float x, float y, float angle, float scale) {
	constant.world = XMMatrixIdentity();
	constant.world *= XMMatrixScaling(256.0f * scale, 256.0f * scale, 1.0f);
	constant.world *= XMMatrixRotationZ(XMConvertToRadians(-angle));
	constant.world *= XMMatrixTranslation(x, -y, 0.0f);

	Graphics::GetInstance().GetDeviceContext().UpdateSubresource(constantBuffer, 0, nullptr, &constant, 0, 0);
	Graphics::GetInstance().GetDeviceContext().DrawIndexed(indexCount, 0, 0);
}
