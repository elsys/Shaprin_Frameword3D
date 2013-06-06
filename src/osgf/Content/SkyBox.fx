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
		float2 iText  : TEXTURE,
        out float4 oPosH  : SV_POSITION,
		out float2 oText : TEXTURE)
{
	oPosH = mul(float4(iPosL, 1.0f), gWVP);
	oText = iText;
}

float4 PS(float4 posH  : SV_POSITION, float2 text : TEXTURE) : SV_Target
{
    //normH.w = 1;
	float4 nPos = posH+float4(1, 1, 1, 1);
	nPos = float4(gText.Sample(mySampler,text).xyz,1);
	
	return float4(nPos);
}
RasterizerState NoCull
{
	CullMode = None;
};
technique10 SkyBoxTech
{
    pass P0
    {
        SetRasterizerState(NoCull);
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}
