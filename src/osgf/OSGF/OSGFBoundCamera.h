#pragma once
#include "OSGFCamera.h"
#include "OSGF3DDrawableComponent.h"
class OSGFBoundCamera
	:public OSGFCamera
{
public:
	OSGFBoundCamera(Game& game,
		const OSGF3DDrawableComponent* boundObject)
		:OSGFCamera(game),mBoundObject(boundObject),
		mDistance(1.0f),mHeight(1.0f),mTargetDistance(1.0f)
	{
	}
	OSGFBoundCamera(const OSGFBoundCamera& cam)
		:OSGFCamera(cam)
	{
		Copy(cam);
	}
	OSGFBoundCamera& operator= (const OSGFBoundCamera& cam)
	{
		if(&cam!=this)
		{
			OSGFCamera::operator=(cam);
			Copy(cam);
		}
		return *this;
	}
	virtual OSGFBoundCamera* Clone()const
	{
		return new OSGFBoundCamera(*this);
	}
	virtual void Update(double dTime)
	{
		OSGFCamera::Update(dTime);
		D3DXVECTOR3 objectPos = mBoundObject->GetTranslation();
		D3DXVECTOR3 forward=mBoundObject->GetFrontGlobalNormalized();
		D3DXVECTOR3 camPos = objectPos - forward*mDistance;
		camPos+= mBoundObject->GetUpGlobalNormalized()*mHeight;
		SetPosition(camPos);
		SetUpVector(mBoundObject->GetUpGlobal());
        SetTarget(objectPos + forward*mTargetDistance);
	}
	void SetCameraDistance(float dist)
	{
		mDistance = dist;
	}
	float GetCameraDistance()
	{
		return mDistance;
	}
	float SetTargetDistance(float dist)
	{
		mTargetDistance = dist;
	}
	float GetTargetDistance()
	{
		return mTargetDistance;
	}
	void SetBoundObject(const OSGF3DDrawableComponent* boundObject)
	{
		mBoundObject = boundObject;
	}
	
	const OSGF3DDrawableComponent* GetBoundObject()const 
	{
		return mBoundObject;
	}
private:
	void Copy(const OSGFBoundCamera& cam)
	{
		mBoundObject = cam.mBoundObject;
		mDistance = cam.mDistance;
		mHeight = cam.mHeight;
		mTargetDistance = cam.mTargetDistance;
	}
	const OSGF3DDrawableComponent* mBoundObject;
	float mDistance;
	float mHeight;
	float mTargetDistance;
};