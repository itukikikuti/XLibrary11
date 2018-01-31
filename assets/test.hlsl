cbuffer Object : register(b0) {
    matrix _world;
};
cbuffer Camera : register(b1) {
    matrix _view;
    matrix _projection;
};
float4 VS(float4 vertex : POSITION) : SV_POSITION {
    float4 output;
    output = mul(_world, vertex);
    output = mul(_view, output);
    output = mul(_projection, output);
    return output;
}
float4 PS(float4 position : SV_POSITION) : SV_TARGET {
	return float4(1, 0, 0, 1);
}
