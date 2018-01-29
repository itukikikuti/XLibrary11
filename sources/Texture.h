class Texture {
	PRIVATE ID3D11Texture2D* texture;
	PRIVATE ID3D11ShaderResourceView* shaderResourceView;
	PRIVATE ID3D11SamplerState* samplerState;

	PUBLIC Texture() {
	}
	PUBLIC ~Texture() {
	}
};
