#pragma once
#include<Windows.h>
#include <cstdio>
#include"OSGFInputElement.h"
enum 
{
	  OSGF_LEFT_MOUSE_BUTTON, 
	  OSGF_RIGHT_MOUSE_BUTTON,
	  OSGF_MIDDLE_MOUSE_BUTTON,
	  OSGF_X1_MOUSE_BUTTON,
	  OSGF_X2_MOUSE_BUTTON
};
class OSGFMouse
	:public OSGFInputElement
{
public:
	OSGFMouse(Game& game)
		:OSGFInputElement(game),mLimted(false)
	{
		mX = 100;
		mY = 100;
		mSpeed = 2;
	}
	virtual void Update(double dTime);
	void LimitTheCursorToScreenCoordinates(bool limt = true)
	{
		mLimted = true;
	}
	LONG GetX()const 
	{
		return mX;
	}
	LONG GetY()const
	{
		return mY;
	}
	LONG GetDeltaX()const
	{
		return mDeltaX;
	}
	LONG GetDeltaY()const
	{
		return mDeltaY;
	}
	SHORT GetWheelRotation()const
	{
		return mWheelRotation;
	}
	bool IsButtonDown(SHORT button)const
	{
		return mButtons[button];
	}
	bool IsButtonUp(SHORT button)const
	{
		return !IsButtonDown(button);
	}
	bool IsButtonJustPressed(SHORT button)const
	{
		return mButtons[button]&!mPrevButtons[button];
	}
	bool IsButtonReleased(SHORT button)const
	{
		return !mButtons[button]&mPrevButtons[button];
	}
	void SetSpeed(UINT speed)
	{
		mSpeed = speed;
	}
	UINT GetSpeed()const
	{
		return mSpeed;
	}
	virtual void HandleInput(const RAWINPUT* ri)
	{
		RAWMOUSE m = ri->data.mouse;
		SetPosition(m);
		SetButtonStates(m);
	}
private:
	void LimitTheCursor();
	void SetPosition(const RAWMOUSE& m)
	{
		if((m.usFlags&0x1) == 0)
		{
			mX += m.lLastX*mSpeed;
			mY += m.lLastY*mSpeed;
		}
	}
	void SetButtonStates(const RAWMOUSE& m)
	{
		USHORT mask = 0x0001;
		USHORT data = m.usButtonFlags;
		for(int i = 0;i < 10; i++)
		{
			mask<<=i;
			if((data&mask)!=0)
				mButtons[i/2] = !(i%2);
			if(data&0x0400)
				mWheelRotation = m.usButtonData;
		}
	}
	int mX,mY;
	LONG mPrevX,mPrevY;
	LONG mDeltaX,mDeltaY;
	SHORT mWheelRotation;
	static const SHORT mButtonsCount = 5;
	bool mButtons[mButtonsCount];
	bool mPrevButtons[mButtonsCount];
	UINT mSpeed;
	bool mLimted;
};