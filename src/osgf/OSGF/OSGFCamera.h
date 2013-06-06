#pragma once
#include "osgfcomponent.h"
#include <D3DX10.h>
#include "Game.h"
class OSGFCamera :public OSGFComponent
{
public:
	OSGFCamera(Game& game)
		:OSGFComponent(game)
	{

	}
	OSGFCamera(const OSGFCamera& cam)
		:OSGFComponent(cam)
	{
		Copy(cam);
	}
	OSGFCamera& operator=(const OSGFCamera& cam)
	{
		if(this!=&cam)
			Copy(cam);
		return *this;
	}
	virtual OSGFCamera* Clone()const 
	{
		return new OSGFCamera(*this);
	}
	float	GetFovY()const
	{
		return fovy;
	}
	void	SetFovY(float value)
	{
		fovy = value;
		needUpdateProjection = true;
	}

	float GetAspectRatio()const
	{
		return aspectRatio;
	}
	void SetAspectRatio(float value)
	{
		aspectRatio = value;
		needUpdateProjection = true;
	}


	float GetNearPlane()const
	{
		return nearPlane;
	}
	void SetNearPlane(float value)
	{
		nearPlane = value;
		needUpdateProjection = true;
	}
	float GetFarPlane()const
	{
		return farPlane;
	}
	void SetFarPlane(float value)
	{
		farPlane = value;
		needUpdateProjection = true;
	}

	const D3DXVECTOR3& GetPosition()const
	{
		return position;
	}
	void SetPosition(const D3DXVECTOR3& value)
	{
		SetLookAt(value, target, upVec);
		needUpdateView = true;
	}

	const D3DXVECTOR3& GetTarget()const
	{
		return target;
	}
	void SetTarget(const D3DXVECTOR3& value)
	{
		SetLookAt(position, value, upVec);
		needUpdateView = true;
	}
	const D3DXVECTOR3& GetUpVector()const
	{
		return upVec;
	}

	void SetUpVector(const D3DXVECTOR3& value)
	{
		SetLookAt(position, target, value);
	}

	const D3DXVECTOR3& GetHeadingVector()const
	{
		return headingVec;
	}

	const D3DXVECTOR3& GetRightVector()const

	{
		return strafeVec;
	}

	const D3DXMATRIX& GetViewMatrix()const
	{
		return viewMatrix;
	}

	const D3DXMATRIX& GetProjectionMatrix()const
	{
		return projectionMatrix;
	}
	D3DXMATRIX GetViewProjectionMatrix()const
	{
		return viewMatrix*projectionMatrix;
	}
	
	void SetPerspectiveFov(float fovy, float aspectRatio, float nearPlane, float farPlane);
	void SetLookAt(D3DXVECTOR3 cameraPos, D3DXVECTOR3 cameraTarget, D3DXVECTOR3 cameraUp);
	virtual void Update(double dTime)
	{
		if (needUpdateView)
			UpdateView();
		if (needUpdateProjection)
			UpdateProjection();
	}
	void OnScreenResize()
	{
		aspectRatio = (float)mGame.GetScreenWidth()/(float)mGame.GetScreenHeight();
		needUpdateProjection = true;
	}
	virtual void Initialize()
	{
		if(IsInitialized())return;
		OSGFComponent::Initialize();
		needUpdateView = true;
		needUpdateProjection = true;
	}
protected:
	virtual void UpdateView()
	{
		D3DXMatrixLookAtLH(&viewMatrix,&position,&target,&upVec);
		needUpdateView = false;
	}

	virtual void UpdateProjection()
	{
		D3DXMatrixPerspectiveFovLH(&projectionMatrix,fovy,aspectRatio,nearPlane,farPlane);
		needUpdateProjection = false;
	}
private:
	void Copy(const OSGFCamera& cam)
	{
		fovy = cam.fovy;
		aspectRatio = cam.aspectRatio;
		nearPlane = cam.nearPlane;
		farPlane = cam.farPlane;
		position = cam.position;
		target = cam.target;
		headingVec = cam.headingVec;
		strafeVec = cam.strafeVec;
		upVec = cam.upVec;
		needUpdateView = cam.needUpdateView;
		needUpdateProjection = cam.needUpdateProjection;
		needUpdateFrustum = cam.needUpdateFrustum;
		viewMatrix = cam.viewMatrix;
		projectionMatrix = cam.projectionMatrix;
	}
	// Perspective projection parameters
	float fovy;
	float aspectRatio;
	float nearPlane;
	float farPlane;

	// Position and target
	D3DXVECTOR3 position;
	D3DXVECTOR3 target;

	// orientation vectors
	D3DXVECTOR3 headingVec;
	D3DXVECTOR3 strafeVec;
	D3DXVECTOR3 upVec;

	// Matrices and updates
	bool needUpdateView;
	bool needUpdateProjection;
	bool needUpdateFrustum;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;

};
