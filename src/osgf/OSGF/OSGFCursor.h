#pragma once
#include "Util.h"
#include "Game.h"
#include "OSGF2DDrawableComponent.h"
class OSGFCursor
	:public OSGF2DDrawableComponent
{
public:
	OSGFCursor(Game& game,OSGF2DDrawableComponent* drawData)
		:OSGF2DDrawableComponent(game)
	{
		SetDrawData(drawData);
	}
	void SetDrawData(OSGF2DDrawableComponent *drawData)
	{
		mDrawData = drawData;
	}
	void Update(double dTime)
	{
		/*mGame.GetMouse();
		const OSGFMouse& m; = mGame.GetMouse();
		SetPosition(m.GetX(),m.GetY());
		mDrawData->SetPosition(GetX(),GetY());*/
	}
	void Render()const 
	{
		mDrawData->Render();
	}
	void DeleteDrawData()
	{
		SafeDelete(mDrawData);
	}
private:
	OSGF2DDrawableComponent* mDrawData;
};