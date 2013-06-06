#include "InputSystem.h"
#include "OSGFMouse.h"
InputSystem::InputSystem()
	
{
	RAWINPUTDEVICE devs[2];
	devs[0].usUsagePage = 0x01;
	devs[0].usUsage = 0x06;
	devs[0].dwFlags = 0;
	devs[0].hwndTarget = 0;
	devs[1].usUsagePage = 0x01; 
	devs[1].usUsage = 0x02; 
	devs[1].dwFlags = 0;
	devs[1].hwndTarget = 0;
	RegisterAndCheckForErrors(devs,2);
}
InputSystem::InputSystem(RAWINPUTDEVICE* devs,UINT count)
{
	RegisterAndCheckForErrors(devs,count);
}
void InputSystem::HandleInput(WPARAM wParam,LPARAM lParam)
{
	UINT dwSize;
	GetRawInputData((HRAWINPUT)lParam,RID_INPUT,NULL,&dwSize,
		sizeof(RAWINPUTHEADER));
	LPBYTE lpb  = new BYTE[dwSize];
	GetRawInputData((HRAWINPUT)lParam,RID_INPUT,lpb,&dwSize,
		sizeof(RAWINPUTHEADER));
	RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(lpb);
	OSGFInputElement* inputElement = mInputElements[raw->header.dwType];
	if(inputElement)
		mInputElements[raw->header.dwType]->HandleInput(raw);
}


InputSystem::~InputSystem(void)
{
}
