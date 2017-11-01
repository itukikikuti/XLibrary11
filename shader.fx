cbuffer ConstantBuffer : register(b0) {
	matrix WORLD;
	matrix VIEW;
	matrix PROJECTION;
	float3 LIGHT_DIRECTION;
};

Texture2D diffuseTexture : register(t0);
SamplerState diffuseTextureSampler: register(s0);

struct VSOutput {
	float4 position : SV_POSITION;
	float4 normal : NORMAL;
	float2 uv : TEXCOORD;
};

VSOutput VS(float4 vertex : POSITION, float4 normal : NORMAL, float2 uv : TEXCOORD) {
	VSOutput output = (VSOutput)0;
	output.position = vertex;
	output.normal = normal;
	output.uv = uv;
	return output;
}

[maxvertexcount(3)]
void GS(triangle VSOutput input[3], inout TriangleStream<VSOutput> stream) {
	for (int i = 0; i < 3; i++) {
		VSOutput output = (VSOutput)0;
		output.position = input[i].position;
		output.position = mul(WORLD, output.position);
		output.position = mul(VIEW, output.position);
		output.position = mul(PROJECTION, output.position);
		output.normal = normalize(mul(WORLD, -input[i].normal));
		output.uv = input[i].uv;
		stream.Append(output);
	}
	stream.RestartStrip();
}

float4 PS(VSOutput output) : SV_TARGET {
	return diffuseTexture.Sample(diffuseTextureSampler, output.uv);
}
