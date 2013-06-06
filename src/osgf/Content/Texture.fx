
cbuffer cbPerObject
{
	float4x4 gWVP;
};

Texture2D gText;
SamplerState mySampler
{
	Filter = ANISOTROPIC;
};
void VS(float3 iPosL  : POSITION,
		float3 iText  : TEXTURE,
        out float4 oPosH  : SV_POSITION,
		out float3 oText: TEXTURE)
{
	oPosH = mul(float4(iPosL, 1.0f), gWVP);
	
    oText = iText;
}

float4 PS(float4 posH  : SV_POSITION, float3 oText: TEXTURE) : SV_Target
{
    return gText.Sample(mySampler,oText);
}

technique10 TextureTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}
