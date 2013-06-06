cbuffer cbPerObject
{
	float4x4 gWVP; 
};
cbuffer cbPerScene
{
	float3 lightSpecular;
	float3 lightAmbient;
	float3 lightDiffuse;
	float3 lightPos;
	float3 eyePos;
}
void VS(float4 iPosL  : POSITION,
		float3 iText  : TEXTURE,
		float3 iNorm  : NORMAL,
        out float4 oPosH  : SV_POSITION,
		out float4 oNorm :NORMAL,
		out float4 oPosL : POSITION)
{
	oPosH = mul(iPosL, gWVP);
	oPosL = iPosL;
	oNorm = float4(iNorm, 0.0f);
}
float4 Diffuse(float4 pos, float4 norm)
{
	return dot(normalize(float4(lightPos,1.0f) - pos),norm);
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
float4 PSDiffuse(float4 posH  : SV_POSITION, float4 iNorm : NORMAL,  float4 iPosL : POSITION ) : SV_Target
{
	float4 col = Diffuse(iPosL,iNorm);
	col.a = 1;
	return col;
}
float4 PSDiffSpec(float4 posH  : SV_POSITION, float4 iNorm : NORMAL,  float4 iPosL : POSITION ) : SV_Target
{
	float4 col = float4(lightAmbient+Diffuse(iPosL,iNorm)*lightDiffuse+Spec(iPosL,iNorm)*lightSpecular,1.0f);
	col.a = 1.0f;
	return col;
}

technique10 DiffuseTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSDiffuse() ) );
    }
}
technique10 DiffuseSpecTech
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSDiffSpec() ) );
		
	}
}