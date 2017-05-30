float4x4 worldMatrix;
float4x4 viewMatrix;
float4x4 projectionMatrix;
float3 lightDirection;
texture meshTexture;

sampler Sampler = sampler_state {
	texture = <meshTexture>;
};

struct VSOutput {
	float4 position : POSITION;
	float3 normal : TEXCOORD0;
	float2 uv : TEXCOORD1;
};

VSOutput VS(float4 vertex : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD0) {
	VSOutput output = (VSOutput)0;
	output.position = mul(vertex, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.normal = normalize(mul(-normal, worldMatrix));
	output.uv = uv;
	return output;
}

float4 PS(float3 normal : TEXCOORD0, float2 uv : TEXCOORD1) : COLOR {
	return (1.0 - tex2D(Sampler, uv)) * saturate(dot(lightDirection, normal));
}

technique main {
	pass P0 {
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}
