float4x4 mat;

struct VSInput {
	float4 vertex : POSITION;
};

struct PSInput {
	float4 position : POSITION;
	float4 color : COLOR0;
};

PSInput VS(VSInput input) {
	PSInput output;
	output.position = mul(input.vertex, mat);
	output.color = input.vertex;
	return output;
}

float4 PS(PSInput input) : COLOR0 {
	return input.color;
}

technique main {
	pass P0 {
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}
