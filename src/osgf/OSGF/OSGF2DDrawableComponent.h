#pragma once
#include "Rectangle.h"
#include "OSGFDrawableComponent.h"
class OSGF2DDrawableComponent
	:public OSGFDrawableComponent
{
public:
	OSGF2DDrawableComponent(Game& game)
		:OSGFDrawableComponent(game),mRect()
	{}
	OSGF2DDrawableComponent(Game& game,const util::Rectangle& rect)
		:OSGFDrawableComponent(game),mRect(rect)
	{}
	OSGF2DDrawableComponent(Game& game,
		LONG left,LONG top,LONG right,LONG bottom) 
		:OSGFDrawableComponent(game),mRect(left,top,right,bottom)
	{}
	virtual void SetRectangle(const util::Rectangle& rect)
	{
		mRect = rect;
	}
	void SetRectangle(LONG left,LONG top,LONG right,LONG bottom)
	{
		SetRectangle(util::Rectangle(left,top,right,bottom));
	}
	void SetRectangle(const RECT& rect)
	{
		SetRectangle(util::Rectangle(rect));
	}
	void SetPosition(LONG x,LONG y)
	{
		mRect.left = x;
		mRect.top = y;
	}
	LONG GetX()const
	{
		return mRect.right;
	}
	LONG GetY()const
	{
		return mRect.top;
	}
	bool IsPointInside(LONG x,LONG y)
	{
		return mRect.IsPointInside(x,y);
	}
	const util::Rectangle& GetRect()const
	{
		return mRect;
	}
private:
	util::Rectangle mRect;
};