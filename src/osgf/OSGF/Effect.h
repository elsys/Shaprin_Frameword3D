#pragma once
#include <D3D10.h>
#include <D3DX10.h>
#include <string>
#include "Util.h"
#include <exception>
class Effect
{
public:
	Effect(std::string effectFile,ID3D10Device* dev)
			:mTech(NULL),mVertexLayout(NULL),mDevice(dev),mFxName(effectFile)
	{
		CreateEffect(effectFile,dev);
	}
	Effect(const Effect& e )
	{
		Copy(e);
	}
	void SetTechique(const std::string& name)
	{
			try
			{
				mTechName = name;
				mTech=mEffect->GetTechniqueByName(name.c_str());
			}
			catch(std::exception e)
			{
				MessageBoxA(NULL,e.what(),"Exception",MB_OK|MB_ICONERROR);	
			}
			
	}
	void SetMatrix(std::string matrixName,D3DXMATRIX* matrix)const
	{
		mEffect->GetVariableByName(matrixName.c_str())->AsMatrix()->SetMatrix(*matrix);
	}
	void SetVector (std::string vectorName,float* data)const
	{
		mEffect->GetVariableByName(vectorName.c_str())->AsVector()->SetFloatVector(data);
	}
	Effect& operator=(const Effect& fx)
	{
		if(this!=&fx)
		{
			SafeDelete(mTech);
			ReleaseCom(mVertexLayout);
			Copy(fx);
		}
		return *this;
	}
	ID3D10EffectShaderResourceVariable* GetVariableAsShaderResource(const std::string& str)const
	{
		return mEffect->GetVariableByName(str.c_str())->AsShaderResource();
	}
	ID3D10Effect* GetEffect()const
	{
		return mEffect;
	}
	ID3D10EffectTechnique* GetEffectTechnique()const
	{
		return mTech;
	}
	ID3D10InputLayout* GetVertexLayout()const 
	{
		return mVertexLayout;
	}
	void CreateInputLayout(const D3D10_INPUT_ELEMENT_DESC* desc,UINT numElements);
	~Effect(void);
private:
	void Copy(const Effect& fx);
	void CreateEffect(std::string effectFile,ID3D10Device* dev); 
	ID3D10Effect* mEffect;
	ID3D10EffectTechnique* mTech;
	ID3D10InputLayout* mVertexLayout;
	ID3D10Device* mDevice;
	std::string mFxName;
	std::string mTechName;
};

