#pragma once
#include <Windows.h>
#include <D3DX10.h>
#include "Util.h"
#include "OSGFMouse.h"
#include "osgf2ddrawablecomponent.h"
class GameState :
	public OSGFDrawableComponent
{
public:

	GameState(Game &game)
		:OSGFDrawableComponent(game),mClearDepthValue(1.0f),
		 mClearStencilValue(0)
	{
	}
	virtual void Initialize()
	{
		if(IsInitialized())return;
		OSGFDrawableComponent::Initialize();	
	}
	virtual void Render()const;
	
	virtual void Update(double dTime)
	{
		OSGFDrawableComponent::Update(dTime);
		HandleInput(dTime);
	}
	virtual void HandleInput(double dTime)=0;
	void SetClearColor(const D3DXCOLOR& color )
	{
		mClearColor = color;
	}
	const D3DXCOLOR& GetClearColor()const
	{
		return mClearColor;
	}
	void SetClearDepthValue(FLOAT value)
	{
		mClearDepthValue = value;
	}
	FLOAT GetClearDepthValue()const
	{
		return mClearDepthValue;
	}
	void SetClearStencilValue(UINT8 value)
	{
		mClearStencilValue = value;
	}
	UINT GetClearStencilValue()const
	{
		return mClearStencilValue;
	}
	virtual ~GameState(void)
	{
		
	}
private:
	D3DXCOLOR mClearColor;
	FLOAT mClearDepthValue;
	UINT8 mClearStencilValue;
	

};

