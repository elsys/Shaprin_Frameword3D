
cbuffer cbPerObject
{
	float4x4 gWVP; 
};

void VS(float3 iPosL  : POSITION,
        out float4 oPosH  : SV_POSITION)
{
	oPosH = mul(float4(iPosL, 1.0f), gWVP);
}

float4 PS(float4 posH  : SV_POSITION) : SV_Target
{
    //normH.w = 1;
	float4 nPos = posH+float4(1, 1, 1, 1);
	nPos = normalize(nPos);
	nPos.a = 1;
	return float4(1,1,1,1);
}
RasterizerState NoCull
{
	CullMode = None;
};
technique10 MonoColorTech
{
    pass P0
    {
        SetRasterizerState(NoCull);
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}
