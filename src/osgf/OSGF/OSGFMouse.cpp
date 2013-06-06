#include "OSGFMouse.h"
#include "Game.h"
void OSGFMouse::Update(double dTime)
{
		LimitTheCursor();
		mDeltaX = mX-mPrevX;
		mDeltaY = mY-mPrevY;
		mPrevX = mX;
		mPrevY = mY;
		for(int i = 0; i < mButtonsCount; i++)
			mPrevButtons[i] = mButtons[i];
}
void OSGFMouse::LimitTheCursor()
{
		if(!mLimted)
		{
			mX = max(mX,0);
			mX = min(mX,mGame.GetScreenWidth());
			mY = max(mY,0);
			mY = min(mY,mGame.GetScreenHeight());
		}
}