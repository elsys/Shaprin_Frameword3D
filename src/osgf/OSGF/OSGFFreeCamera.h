#pragma once
#include "OSGFCamera.h"
#include "Game.h"
class OSGFFreeCamera :public  OSGFCamera
{
public: 
OSGFFreeCamera(Game& game)
		: OSGFCamera(game),zoomSpeed(0.003f),moveSpeed(0.001f)
	{
	}
	OSGFFreeCamera(Game& game,D3DXVECTOR3 cameraPosition, 
		D3DXVECTOR3 cameraTarget)
		: OSGFCamera(game)
	{
		SetLookAt(cameraPosition, cameraTarget, D3DXVECTOR3(0,1,0));
	}
	OSGFFreeCamera(const OSGFFreeCamera& cam)
		:OSGFCamera(cam)
	{
		Copy(cam);
	}
	OSGFFreeCamera& operator=(const OSGFFreeCamera& cam)
	{
		if(&cam!=this)
		{
			OSGFCamera::operator=(cam);
			Copy(cam);
		}
		return *this;
	}
	virtual OSGFFreeCamera* Clone()const
	{
		return new OSGFFreeCamera(*this);
	}
	virtual void Initialize()
	{
		if(IsInitialized())
			return;
		OSGFCamera::Initialize();
		screenWidthHalf  = mGame.GetScreenWidth()  / 2;
		screenHeightHalf = mGame.GetScreenHeight() / 2;
	}
	float GetZoomSpeed()
	{
		return zoomSpeed; 
	}
	void SetZoomSpeed(float value)
	{ 
		zoomSpeed = value; 
	}

	float GetMoveSpeed()
	{ 
		return moveSpeed; 
	}
	void SetMoveSpeed(float value)
	{ 
		moveSpeed = value; 
	}
	void ZoomIn()
	{
		SetPosition(GetPosition()-GetPosition() * zoomSpeed);
	}

	void ZoomOut()
	{
		SetPosition(GetPosition()+GetPosition() * zoomSpeed);
	}

	void MoveLeft()
	{
		SetTarget(GetTarget()   + D3DXVECTOR3(-1,0,0) * moveSpeed);
		SetPosition(GetPosition()+ D3DXVECTOR3(-1,0,0) * moveSpeed);
	}
	void MoveRight()
	{
		SetTarget(GetTarget()   + D3DXVECTOR3(1,0,0) * moveSpeed);
		SetPosition(GetPosition()+ D3DXVECTOR3(1,0,0) * moveSpeed);
	}
	void MoveForward()
	{
		SetTarget(GetTarget()   + D3DXVECTOR3(0,0,1) * moveSpeed);
		SetPosition(GetPosition()+ D3DXVECTOR3(0,0,1) * moveSpeed);

	}
	void MoveBack()
	{
		SetTarget(GetTarget()   + D3DXVECTOR3(0,0,-1) * moveSpeed);
		SetPosition(GetPosition() + D3DXVECTOR3(0,0,-1) * moveSpeed);
	}
	void MoveUp()
	{
		SetTarget(GetTarget() + D3DXVECTOR3(0,1,0)*moveSpeed);
		SetPosition(GetPosition() + D3DXVECTOR3(0,1,0)*moveSpeed);
	}
	void MoveDown()
	{
		SetTarget(GetTarget() + D3DXVECTOR3(0,-1,0)*moveSpeed);
		SetPosition(GetPosition() + D3DXVECTOR3(0,-1,0)*moveSpeed);
	}
	void MoveTo(float x, float z)
	{
		SetTarget( D3DXVECTOR3((float)x, GetTarget().y, z - 500.0f));
		SetPosition(D3DXVECTOR3((float)x, GetPosition().y, (float)z));
	}
	void MoveTo(const D3DXVECTOR2 &vec)
	{
		MoveTo((int)vec.x, (int)vec.y);
	}
private:
	void Copy(const OSGFFreeCamera& cam)
	{
		zoomSpeed = cam.zoomSpeed;
		moveSpeed = cam.moveSpeed;
		screenWidthHalf = cam.screenWidthHalf;
		screenHeightHalf = cam.screenHeightHalf;
	}
	//Movement and zoom speed
	float  zoomSpeed ;
	float  moveSpeed ;

	//Half the screen resolution
	int screenWidthHalf;
	int screenHeightHalf;

};
