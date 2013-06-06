#include<D3D10.h>
#include<DxErr.h>
#include "Effect.h"
#include "Util.h"
#include "Game.h"
using namespace std;
void Effect::CreateInputLayout(const D3D10_INPUT_ELEMENT_DESC* desc,UINT numElements)
{
	if(!mTech)
	{
		throw "Technique not set!";
	}
	D3D10_PASS_DESC passDesc;
	//inpDescs = InputDescriptions(desc,numElements);
	HR(mTech->GetPassByIndex(0)->GetDesc(&passDesc));
	HR(mDevice->CreateInputLayout(desc,numElements,passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize,&mVertexLayout));

}
void Effect::Copy(const Effect& fx)
{
	mDevice = fx.mDevice;
	mEffect = fx.mEffect;
	mEffect->AddRef();
	if(fx.mTech)
	{
		SetTechique(fx.mTechName);
	}
	if(fx.mVertexLayout)
	{
		mVertexLayout = fx.mVertexLayout;
		mVertexLayout->AddRef();
	}
}
void Effect::CreateEffect(std::string effectFile,ID3D10Device* dev)
{
	mFxName = effectFile;
	mDevice = dev;
	DWORD shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
	ID3D10Blob* compilationErrors = 0; 
	HRESULT hr = D3DX10CreateEffectFromFileA(effectFile.c_str(), 0, 0, "fx_4_0", shaderFlags,
		0 ,mDevice, 0, 0, &mEffect, &compilationErrors, 0);
	if(FAILED(hr))
	{
		string title("Error in");
		title+=effectFile;
		MessageBoxA(NULL,DXGetErrorStringA(hr),"Error",MB_OK);
		if(compilationErrors)
		{
			MessageBoxA(NULL,reinterpret_cast<LPCSTR>(compilationErrors->GetBufferPointer()),
				title.c_str(),MB_OK|MB_ICONERROR);
		}
		ReleaseCom(compilationErrors);
		
	}
}
Effect::~Effect(void)
{
	ReleaseCom(mEffect);
	ReleaseCom(mVertexLayout);
}
