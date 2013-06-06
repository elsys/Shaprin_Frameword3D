#pragma once
#include <Windows.h>
inline bool IsKeyDown(int vKey)
{
	return (GetAsyncKeyState(vKey)&0x8000)!=0;
}
inline bool IsKeyUp(int vKey)
{
	return !IsKeyDown(vKey);
}
inline bool IsKeyReleased(int vKey)
{
	SHORT state = GetAsyncKeyState(vKey);
	char des[16];
	sprintf(des,"%d && %d \n",(state & 0x1),! (state & 0x8000));
	OutputDebugStringA(des);
	return ((state & 0x1)  &&  ! (state & 0x8000)) != 0;		
}
inline bool IsKeyJustPressed(int vKey)
{
	SHORT state = GetAsyncKeyState(vKey);
	return ((state & 0x8000) && ! (state & 0x1)) !=0;
}

