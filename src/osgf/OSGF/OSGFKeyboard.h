#pragma once
#include <vector>
#include <Windows.h>
#include "OSGFInputElement.h"
class OSGFKeyboard :
	public OSGFInputElement
{
public:
	OSGFKeyboard(Game& game)
		:OSGFInputElement(game),
		mCurrentState(0xFFFF,1),mPrevState(0xFFFF,1)
	{

	}
	virtual void Update(double dTime)
	{
		mPrevState = mCurrentState;
	}
	const BYTE& operator[](USHORT index)const
	{
		return mCurrentState[index];
	}
	virtual void HandleInput(const RAWINPUT* ri)
	{
		RAWKEYBOARD k= ri->data.keyboard;
		mCurrentState[k.VKey] = k.Flags & 0x01;
	}
	bool IsKeyDown(USHORT vKey)const
	{
		return mCurrentState[vKey]==0;
	}
	bool IsKeyUp(USHORT vKey)const
	{
		return !IsKeyDown(vKey);
	}
	bool IsKeyReleased(USHORT vKey)const
	{
		return (mCurrentState[vKey])&&!mPrevState[vKey];
	}
	bool IsKeyJustPressed(USHORT vKey)const
	{
		return (!mCurrentState[vKey])&&(mPrevState[vKey]);
	}
	virtual ~OSGFKeyboard(void)
	{
	}
private:
	std::vector<BYTE> mCurrentState;
	std::vector<BYTE> mPrevState;
};

