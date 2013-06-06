#pragma once
#include <D3DX10.h>
#include "osgfdrawablecomponent.h"
class OSGFGameScene :
	public OSGFDrawableComponent
{
public:
	OSGFGameScene(void);
	virtual ~OSGFGameScene(void);
private:
	D3DXCOLOR mAmbientLight;
	D3DXCOLOR mDiffuseLight;
	D3DXCOLOR mSpecualLight;
};

