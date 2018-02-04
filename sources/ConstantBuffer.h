class ConstantBuffer {
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer = nullptr;

	PUBLIC ConstantBuffer(size_t size) {
		Setup(size);
	}
	PUBLIC virtual ~ConstantBuffer() {
	}
	PUBLIC void Attach(int slot, void* constantData) {
		if (constantData == nullptr) return;
		App::GetGraphicsContext().UpdateSubresource(constantBuffer.Get(), 0, nullptr, constantData, 0, 0);
		App::GetGraphicsContext().VSSetConstantBuffers(slot, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().HSSetConstantBuffers(slot, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().DSSetConstantBuffers(slot, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().GSSetConstantBuffers(slot, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().PSSetConstantBuffers(slot, 1, constantBuffer.GetAddressOf());
	}
	PROTECTED void Setup(size_t size) {
		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth = static_cast<UINT>(size);
		constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = 0;
		App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, constantBuffer.GetAddressOf());
	}
};
