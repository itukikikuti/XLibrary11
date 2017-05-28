float4x4 mat;

float4 VS(float4 vertex : POSITION) : POSITION {
	return mul(vertex, mat);
}

float4 PS() : COLOR0 {
	return float4(1.0, 1.0, 1.0, 1.0);
}

technique main {
	pass P0 {
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}
