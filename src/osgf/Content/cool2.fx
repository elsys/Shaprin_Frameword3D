
cbuffer cbPerObject
{
	float4x4 gWVP; 
};

void VS(float3 iPosL  : POSITION,
	    float3 iText  : TEXTURE,
		float3 iNorm  : NORMAL,
        out float4 oPosH  : SV_POSITION,
		out float3 oText  : TEXTURE,
		out float4 oNormal : NORMAL)
{
	oPosH = mul(float4(iPosL, 1.0f), gWVP);
	oNormal = float4(iNorm,1);
	oText = iText;
}
RasterizerState NoCull
{
	CullMode = None;
};
float4 PS(float4 posH  : SV_POSITION, float3 iText : TEXTURE ,float4 normH : NORMAL ) : SV_Target
{
	return float4(iText,1.0f);
}

technique10 Cool
{
    pass P0
    {
        SetRasterizerState(NoCull);
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}
