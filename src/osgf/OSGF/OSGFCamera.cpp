#include "OSGFCamera.h"
void OSGFCamera::SetPerspectiveFov(float fovy, float aspectRatio, float nearPlane, float farPlane)
{
	this->fovy = fovy;
	this->aspectRatio = aspectRatio;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;

	needUpdateProjection = true;
}

void OSGFCamera::SetLookAt(D3DXVECTOR3 cameraPos, D3DXVECTOR3 cameraTarget, D3DXVECTOR3 cameraUp)
{
	this->position = cameraPos;
	this->target = cameraTarget;
	this->upVec = cameraUp;

	headingVec = cameraTarget - cameraPos;
	D3DXVec3Normalize(&headingVec,&headingVec);
	upVec = cameraUp;
	D3DXVec3Cross(&strafeVec,&headingVec, &upVec);
	needUpdateView = true;
}