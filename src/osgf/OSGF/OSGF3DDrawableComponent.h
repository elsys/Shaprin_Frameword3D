#pragma once
#include <D3DX10math.h>
#include "OSGFCamera.h"
#include "OSGFLevel.h"
#include "OSGFDrawableComponent.h"
class OSGF3DDrawableComponent
	:public OSGFDrawableComponent
{
public:
	OSGF3DDrawableComponent(Game& game)
		:OSGFDrawableComponent(game),mCamera(NULL),mLight(NULL)
	{
	}
	OSGF3DDrawableComponent(const OSGF3DDrawableComponent& o)
		:OSGFDrawableComponent(o),mCamera(NULL),mLight(NULL)
	{
		Copy(o);
	}
	virtual OSGF3DDrawableComponent* Clone()const
	{
		return new OSGF3DDrawableComponent(*this);
	}
	virtual void Render()const
	{
		mGame.GetDevice()->OMSetDepthStencilState(0, 0);
	}
	virtual void Initialize()
	{
		D3DXMatrixIdentity(&mScaling);
		D3DXMatrixIdentity(&mRotation);
		D3DXMatrixIdentity(&mTranslation);
	}
	virtual void Update(double dTime)
	{
		mWorld = mScaling*mRotation*mTranslation;
		mWVP = mWorld*mCamera->GetViewMatrix()*mCamera->GetProjectionMatrix();
		D3DXVECTOR4 vec;
		D3DXVec3Transform(&vec,&mUpLocal,&mWorld);
		mUpGlobal = D3DXVECTOR3(vec.x,vec.y,vec.z);
		D3DXVec3Transform(&vec,&mFrontLocal,&mWorld);
		mFrontGlobal = D3DXVECTOR3(vec.x,vec.y,vec.z);
	}
	virtual void SetCamera(const OSGFCamera* cam)
	{
		mCamera = cam;
	}
	virtual void SetLight(const Light* light)
	{
		mLight = light;
	}
	const OSGFCamera* GetCamera()const 
	{
		return mCamera;
	}
	const Light* GetLight()const 
	{
		return mLight;
	}
	const D3DXMATRIX& GetRotationMatrix()const
	{
		return mRotation;
	}
	D3DXVECTOR3 GetTranslation()const
	{
		return D3DXVECTOR3(mTranslation._41,mTranslation._42,mTranslation._43);
	}
	const D3DXMATRIX& GetTranslationMatrix()const
	{
		return mTranslation;
	}
	D3DXVECTOR3 GetScaling()const
	{
		return D3DXVECTOR3(mScaling._11,mScaling._22,mScaling._33);
	}
	const D3DXMATRIX& GetScalingMatrix()const
	{
		return mScaling;
	}
	D3DXMATRIX& GetWVPMatrix() 
	{
		return mWVP;
	}
	const D3DXMATRIX& GetWVPMatrix()const 
	{
		return mWVP;
	}
	const D3DXMATRIX& GetWorldMatrix()const
	{
		return mWorld;
	}
	virtual void Move(const D3DXVECTOR3 d)
	{
		Move(d.x,d.y,d.z);
	}
	virtual void Move(float x,float y,float z)
	{
		mTranslation._41+=x;
		mTranslation._42+=y;
		mTranslation._43+=z;
	}
	virtual void RotateX(float a)
	{
		D3DXMATRIX dispMatrix;
		D3DXMatrixRotationX(&dispMatrix,a);
		mRotation*=dispMatrix;
	}
	virtual void RotateY(float a)
	{
		D3DXMATRIX dispMatrix;
		D3DXMatrixRotationY(&dispMatrix,a);
		mRotation*=dispMatrix;
	}
	virtual void RotateZ(float a)
	{
		D3DXMATRIX dispMatrix;
		D3DXMatrixRotationZ(&dispMatrix,a);
		mRotation*=dispMatrix;
	}
	virtual void Scale(float x,float y,float z)
	{
		mScaling._11+=x;
		mScaling._22+=y;
		mScaling._33+=z;
	}
	virtual void Scale(D3DXVECTOR3 s)
	{
		Scale(s.x,s.y,s.z);
	}
	virtual void SetScaling(const D3DXMATRIX& s)
	{
		mScaling = s;
	}
	virtual void SetScaling(float x,float y,float z)
	{
		D3DXMatrixScaling(&mScaling,x,y,z);
	}
	virtual void SetScaling(D3DXVECTOR3 s)
	{
		SetScaling(s.x,s.y,s.z);
	}
	virtual void SetTranslation(const D3DXMATRIX& t)
	{
		mTranslation = t;
	}
	virtual void SetTranslation(float x,float y,float z)
	{
		D3DXMatrixTranslation(&mTranslation,x,y,z);
	}
	virtual void SetTranslation(const D3DXVECTOR3& v)
	{
		SetTranslation(v.x,v.y,v.z);
	}
	virtual void SetRotation(D3DXMATRIX r)
	{
		mRotation = r;
	}
	virtual void SetRotation(float x,float y,float z)
	{
		D3DXMatrixRotationYawPitchRoll(&mRotation,y,x,z);
	}
	virtual void SetRotation(const D3DXQUATERNION& q)
	{
		D3DXMatrixRotationQuaternion(&mRotation,&q);
	}
	void SetFrontLocal(const D3DXVECTOR3& front)
	{
		mFrontLocal = front;
	}
	const D3DXVECTOR3& GetFrontLocal()
	{
		return mFrontLocal;
	}
	D3DXVECTOR3 GetFrontLocalNormalized()const
	{
		D3DXVECTOR3 res;
		D3DXVec3Normalize(&res,&mFrontLocal);
		return res;
	}
	D3DXVECTOR3 GetFrontGlobalNormalized()const
	{
		D3DXVECTOR3 res;
		D3DXVec3Normalize(&res,&mFrontGlobal);
		return res;
	}
	const D3DXVECTOR3& GetFrontGlobal()const
	{
		return mFrontGlobal;
	}
	void SetUpLocal(const D3DXVECTOR3& up)
	{
		mUpLocal = up;
	}
	const D3DXVECTOR3& GetUpLocal()const
	{
		return mUpLocal;
	}
	const D3DXVECTOR3& GetUpGlobal()const
	{
		return mUpGlobal;
	}
	const D3DXVECTOR3 GetUpLocalNormalized()const
	{
		D3DXVECTOR3 res;
		D3DXVec3Normalize(&res,&mUpLocal);
		return res;
	}
	const D3DXVECTOR3 GetUpGlobalNormalized()const
	{
		D3DXVECTOR3 res;
		D3DXVec3Normalize(&res,&mUpGlobal);
		return res;
	}
	virtual OSGF3DDrawableComponent& operator=(const OSGF3DDrawableComponent& o)
	{
		if(this!=&o)
		{
			Copy(o);
		}
		return *this;
	}
protected:
	D3DXMATRIX mScaling;
	D3DXMATRIX mTranslation;
	D3DXMATRIX mRotation;
private:

	void Copy(const OSGF3DDrawableComponent& o)
	{
		SetScaling(o.GetScalingMatrix());
		SetTranslation(o.GetTranslationMatrix());
		SetRotation(o.GetRotationMatrix());
		mWVP = o.mWVP;
		mWorld = o.mWorld;
		SetCamera(o.mCamera);
		SetLight(o.mLight);
	}
	D3DXMATRIX mWVP;
	D3DXMATRIX mWorld;
	D3DXVECTOR3 mFrontLocal;
	D3DXVECTOR3 mUpLocal;
	D3DXVECTOR3 mFrontGlobal;
	D3DXVECTOR3 mUpGlobal;
	const OSGFCamera* mCamera;
	const Light* mLight;
};