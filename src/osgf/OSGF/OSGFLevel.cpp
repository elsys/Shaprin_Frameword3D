#include"OSGFLevel.h"
void OSGFLevel::InitializeCamera()
{
	OSGFCamera cam(mGame);
	cam.SetFarPlane(1000);
	cam.SetNearPlane(1);
	cam.SetFovY((float)D3DX_PI*0.33);
	cam.SetLookAt(D3DXVECTOR3(0,3.50,-3.50),D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,1,0));
	cam.Initialize();
	SetCamera(cam);
}