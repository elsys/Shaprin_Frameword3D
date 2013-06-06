#pragma once
#include <D3D10.h>
#include <string>
#include "osgf3ddrawablecomponent.h"
#include "Effect.h"
#include "OSGFCamera.h"
#include "Util.h"
#include "Game.h"
class OSGF3DModel :
	public OSGF3DDrawableComponent
{
public:
	OSGF3DModel(Game& game,const std::string& mEffect,const std::string& technique);
	OSGF3DModel(const OSGF3DModel& m)
		:OSGF3DDrawableComponent(m)
	{
		Copy(m);
	}
	OSGF3DModel& operator=(const OSGF3DModel& m)
	{
		if(&m!=this)
		{
			OSGF3DDrawableComponent::operator=(m);
			Copy(m);
		}
		return *this;
	}
	virtual OSGF3DModel* Clone()const
	{
		return new OSGF3DModel(*this);
	}
	virtual void Initialize();
	virtual void Update(double dTime)
	{
		OSGF3DDrawableComponent::Update(dTime);
	}
	void CreateInputLayout(const D3D10_INPUT_ELEMENT_DESC* el,int n)
	{
		mEffect->CreateInputLayout(el,n);
	}
	void SetTexture(const std::string& file);
	virtual void Render()const;
	virtual void Load()
	{
		if(IsLoaded())return;
		OSGF3DDrawableComponent::Load();
		mEffect = new Effect(mEffectName,mGame.GetDevice());
		mEffect -> SetTechique(mTechName);
	}
	virtual void Unload()
	{
		if(!IsLoaded())return;
		OSGF3DDrawableComponent::Unload();
		SafeDelete(mEffect);
	}
	void CreateVertexBuffer(void* verts,UINT buferSize,UINT vertexSize,
							UINT CPUAccessFlags=0,UINT miscFlags=0,
							D3D10_USAGE usage = D3D10_USAGE_DEFAULT);
	void CreateIndexBuffer(DWORD indices[],UINT size,UINT CPUAccessFlags=0,
		UINT miscFlags=0,D3D10_USAGE usage = D3D10_USAGE_DEFAULT);
	virtual ~OSGF3DModel(void);
protected:
	void Copy(const OSGF3DModel& m)
	{
		mEffect = m.mEffect;
		mEffectName = m.mEffectName;
		mTechName = m.mTechName;
		mVertexSize = m.mVertexSize;
		mNIndices = m.mNIndices;
		mPrimitiveTopology = m.mPrimitiveTopology;
		if(m.mText)
			SetTexture(m.mTextName);
		mVertexBuffer = m.mVertexBuffer;
		mVertexBuffer->AddRef();
		mIndexBuffer = m.mIndexBuffer;
		mIndexBuffer->AddRef();
	}
	ID3D10Buffer* mVertexBuffer;
	ID3D10Buffer* mIndexBuffer;
	Effect* mEffect;
	std::string mEffectName;
	std::string mTechName;
	UINT mVertexSize;
	UINT mNIndices;
	D3D10_PRIMITIVE_TOPOLOGY mPrimitiveTopology;
	ID3D10ShaderResourceView* mText;
	std::string mTextName;
};


