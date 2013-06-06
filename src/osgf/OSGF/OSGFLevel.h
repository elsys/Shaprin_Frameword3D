#pragma once
#include <D3DX10.h>
#include "Game.h"
#include "OSGFCamera.h"
#include "GameState.h"
struct Light
{
	D3DXVECTOR3 ambientLight;
	D3DXVECTOR3 diffuseLight;
	D3DXVECTOR3 specularLight;
	D3DXVECTOR3 lightPos;
};
class OSGFLevel
	:public GameState
{
public:
	OSGFLevel(Game& game)
		:GameState(game),mCamera(NULL)
	{
		SetLight(1,1,1,1,1,1,1,1,1,0,0,0);
	}
	OSGFLevel(const OSGFLevel& l)
		:GameState(l),mCamera(l.mCamera)
	{

	}
	virtual void OnScreenResize(WPARAM wParam,LPARAM lParam)
	{
		if(mCamera)
			mCamera->OnScreenResize();
	}
	virtual void Initialize()
	{
		if(IsInitialized())
			return;
		GameState::Initialize();
	}
	virtual void Update(double dTime)
	{
		GameState::Update(dTime);
		mCamera->Update(dTime);
	}
	virtual void InitializeCamera();
	void SetCamera(const OSGFCamera& camera)
	{
		SafeDelete(mCamera);
		mCamera = camera.Clone();
	}
	const OSGFCamera* GetCamera()const
	{
		return mCamera;
	}
	void SetLight(const Light& light)
	{
		mLight = light;
	} 
	void SetLight(const D3DXVECTOR3& ambient,
		const D3DXVECTOR3& diffuse, const D3DXVECTOR3& specular,const D3DXVECTOR3& pos)
	{
		SetSpecular(specular);
		SetDiffuse(diffuse);
		SetAmbient(ambient);
		SetLightPosition(pos);
	}
	void SetLight(float ar, float ag, float ab,
				  float dr, float dg, float dd,
				  float sr, float sg, float sd,
				  float x,  float y , float z )
	{
		SetAmbient(ar, ag, ab);
		SetDiffuse(dr, dg, dd);
		SetSpecular(sr, sg, sd);
		SetLightPosition(x, y, z);
	}
	void SetLightPosition(const D3DXVECTOR3& pos)
	{
		mLight.lightPos = pos;
	}
	void SetLightPosition(float x,float y,float z)
	{
		SetLightPosition(D3DXVECTOR3(x, y, z));
	}
	void SetSpecular(const D3DXVECTOR3& spec)
	{
		mLight.specularLight = spec;
	}
	void SetSpecular(float sr,float sg,float sb)
	{
		SetSpecular(D3DXVECTOR3(sr,sg,sb));
	}
	void SetDiffuse(const D3DXVECTOR3& diff)
	{
		mLight.diffuseLight = diff;
	}
	void SetDiffuse(float dr,float dg,float db)
	{
		SetDiffuse(D3DXVECTOR3(dr, dg, db));
	}
	void SetAmbient(const D3DXVECTOR3 ambient)
	{
		mLight.ambientLight = ambient;
	}
	void SetAmbient(float ar, float ag, float ab)
	{
		SetAmbient(D3DXVECTOR3(ar,ag,ab));
	}
	void SetLightPos(const D3DXVECTOR3& pos)
	{
		mLight.lightPos = pos;
	}
	void SetLightPos(float x,float y,float z)
	{
		SetLightPos(D3DXVECTOR3(x,y,z));
	}
	const Light& GetLight()const
	{
		return mLight;
	}
	const D3DXVECTOR3& GetSpecular()const 
	{
		return mLight.specularLight;
	}
	const D3DXVECTOR3& GetDiffuse()const
	{
		return mLight.diffuseLight;
	}
	const D3DXVECTOR3& GetAmbient()const
	{
		return mLight.ambientLight;
	}
	const D3DXVECTOR3& GetPosition()const
	{
		return mLight.lightPos;
	}
protected:
	OSGFCamera* mCamera;
private:
	Light mLight;
	
};