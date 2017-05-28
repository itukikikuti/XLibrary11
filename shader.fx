float4x4 mat;

struct VSOutput {
	float4 position : POSITION;
	float4 color : COLOR0;
};

VSOutput VS(float4 vertex : POSITION) {
	VSOutput output;
	output.position = mul(vertex, mat);
	output.color = vertex;
	return output;
}

float4 PS(VSOutput input) : COLOR0 {
	return input.color;
}

technique main {
	pass P0 {
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}
