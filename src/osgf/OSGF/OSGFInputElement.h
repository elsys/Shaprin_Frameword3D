#pragma once
#include <windows.h>
#include "OSGFComponent.h"
class OSGFInputElement
	:public OSGFComponent
{
public:
	OSGFInputElement(Game &game)
		:OSGFComponent(game)
	{
	}
	virtual void HandleInput(const RAWINPUT* ri)=0;
};