cbuffer cbPerScene
{
	float3 lightSpecular;
	float3 lightAmbient;
	float3 lightDiffuse;
	float3 lightPos;
	float3 eyePos;
}
Texture2D gText;
SamplerState mySampler
{
	Filter = ANISOTROPIC;
};
cbuffer cbPerObject
{
	matrix gWVP;
	float3 mtrlSpecular;
	float3 mtrlAmbient;
	float3 mtrlDiffuse;
}
float4 Diffuse(float4 pos, float4 norm)
{
	return dot(normalize(float4(lightPos,0.0f) - pos),norm);
}
float4 Spec(float4 pos, float4 norm)
{
	float4 L = pos - float4(lightPos,1.0f);
    float4 N = norm;
    float4 V = normalize(float4(eyePos, 1.0f) - pos);
    float4 R = normalize(reflect(L, N));
    float4 color = pow(saturate(dot(R, V)), 8);
    return color;
}
void VS(float3 iPosL : POSITION, 
		float3 iText : TEXTURE,
		float3 iNorm : NORMAL,
		out float4 oPosH : SV_POSITION,
		out float4 oNorm : NORMAL,
		out float4 oPosL : POSITION,
		out float3 oText : TEXTURE)
{
	oPosH = mul(float4(iPosL,1.0f),gWVP);
	oNorm = float4(iNorm,0.0f);
	oPosL = float4(iPosL,1.0f);
	oText = iText;
}
float4 PS(float4 iPosH : SV_POSITION, float4 iNorm : NORMAL, 
			float4 iPosL : POSITION, float3 iText : TEXTURE) : SV_TARGET
{
	float3 col = mtrlAmbient*lightAmbient+float3(0.2, 0.2, 0.2);
	col+=mtrlDiffuse*lightDiffuse*Diffuse(iPosL,iNorm).xyz;
	col+=mtrlSpecular*lightSpecular*Spec(iPosL,iNorm).xyz;
	col*=gText.Sample(mySampler,iText).xyz;
	return float4(col, 1.0);
}
RasterizerState NoCull
{
	CullMode = None;
};
technique10 LightAndTexture
{
	pass P0
	{
		SetVertexShader( CompileShader(vs_4_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader( CompileShader(ps_4_0, PS()));
	}
}