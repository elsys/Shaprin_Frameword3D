#pragma once
#include <Windows.h>
#include "IDrawable.h"
#include "OSGFComponent.h"
class OSGFDrawableComponent :
	public OSGFComponent,public IDrawable
{
public:
	virtual void Update(double deltaTime)
	{
			
	}
	virtual void OnScreenResize(WPARAM wParam,LPARAM lParam)
	{}
protected:
	OSGFDrawableComponent(Game& game)
		:OSGFComponent(game)
	{
	}
	OSGFDrawableComponent(const OSGFDrawableComponent& dc)
		:OSGFComponent(dc)
	{
		
	}
};
