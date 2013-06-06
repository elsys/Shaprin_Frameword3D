#pragma once
#include <Windows.h>
#include <exception>
#include "OSGFInputElement.h"
class InputSystem
{
public:
	InputSystem();
	InputSystem(RAWINPUTDEVICE* devs,UINT count);
	void SetKeyboard(OSGFInputElement* keyboard)
	{
		mInputElements[RIM_TYPEKEYBOARD] = keyboard;
	}
	void SetMouse(OSGFInputElement* mouse)
	{
		mInputElements[RIM_TYPEMOUSE] = mouse;
	}
	void HandleInput(WPARAM wParam,LPARAM lParam);
	~InputSystem(void);
private:
	OSGFInputElement* mInputElements[3];
	void RegisterAndCheckForErrors(RAWINPUTDEVICE* devs,UINT count)
	{
		if(!RegisterRawInputDevices(devs,count,sizeof(devs[0])))
		{
			throw std::exception("Error in registering input devices.Error code"+
				HRESULT_FROM_WIN32(GetLastError()));
		}
	}

};

