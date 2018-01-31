struct Transform {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 angles;
	DirectX::XMFLOAT3 scale;
};

struct Vertex {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 texcoord;
	DirectX::XMFLOAT3 normal;

	//Vertex(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 texcoord, DirectX::XMFLOAT3 normal) {
	//	this->position = position;
	//	this->texcoord = texcoord;
	//	this->normal = normal;
	//}
};
