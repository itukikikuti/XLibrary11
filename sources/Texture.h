class Texture {
	PRIVATE Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;

	PUBLIC Texture() {
	}
	PUBLIC ~Texture() {
	}
};
