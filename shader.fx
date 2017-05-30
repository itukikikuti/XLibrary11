float4x4 worldMatrix;
float4x4 viewMatrix;
float4x4 projectionMatrix;
float3 lightDirection;

struct VSOutput {
	float4 position : POSITION;
	float3 normal : TEXCOORD0;
};

VSOutput VS(float4 vertex : POSITION, float3 normal : NORMAL) {
	VSOutput output = (VSOutput)0;
	output.position = mul(vertex, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.normal = normalize(mul(-normal, worldMatrix));
	return output;
}

float4 PS(float3 normal : TEXCOORD0) : COLOR {
	return saturate(dot(lightDirection, normal)) + float4(0.25, 0.25, 0.25, 1.0);
}

technique main {
	pass P0 {
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}
