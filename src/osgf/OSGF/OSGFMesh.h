#pragma once
#include<string>
#include<D3DX10.h>
#include "Game.h"
#include "OSGFLevel.h"
#include "Effect.h"
#include "OSGFCamera.h"
#include "MaterialContainer.h"
#include "osgf3ddrawablecomponent.h"
class OSGFMesh :
	public OSGF3DDrawableComponent
{
public:
	OSGFMesh(Game&game,ID3DX10Mesh* mesh,std::string effect,std::string tech,
		const MaterialContainer& mtrlContainer);
	OSGFMesh(const OSGFMesh& m)
		:OSGF3DDrawableComponent(m.mGame),mEffect(m.mEffect)
	{
		Copy(m);
	}
	virtual OSGFMesh* Clone()const
	{
		return new OSGFMesh(*this);
	}

	OSGFMesh& operator=(const OSGFMesh& m)
	{
		if(this!=&m)
		{
			Clean();
			Copy(m);
		}
		return *this;
	}
	void SetMesh(ID3DX10Mesh* mesh)
	{
		ReleaseCom(mMesh);
		mMesh = mesh;
		mMesh->AddRef();
	}
	void SetMaterials(const MaterialContainer& materials)
	{
		mMaterials = materials;
	}
	UINT GetNubmerOfSubsets()
	{
		return mNubmerSubsets;
	}
	virtual void Render() const;
	virtual void Initialize()
	{
		if(IsInitialized())return;
		OSGF3DDrawableComponent::Initialize();
	}
	virtual ~OSGFMesh(void)
	{
		Clean();
	}
private:
	void Copy(const OSGFMesh& m);	
	void Clean()
	{
		mMesh->Release();
	}
	UINT mNubmerSubsets;
	ID3DX10Mesh *mMesh;
	Effect mEffect;
	MaterialContainer mMaterials;
};

