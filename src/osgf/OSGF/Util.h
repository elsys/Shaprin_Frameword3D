#pragma once
#include <windows.h>
#include <dxerr.h>
#include <D3DX10math.h>
#include <D3DX10.h>
#include <string>
#include <btBulletDynamicsCommon.h>
inline void ReleaseCom(IUnknown* com)
{
	if(com&&(UINT)com!=0xcdcdcdcd)com->Release();
}
inline void SafeDelete(void * obj)
{
	if(obj==NULL)
	{
		delete obj;
		obj = NULL;
	}
}

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                              \
	{                                                          \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
		}													   \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif
const D3DXCOLOR OSGFCOLOR_WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR OSGFCOLOR_BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR OSGFCOLOR_RED(1.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR OSGFCOLOR_GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR OSGFCOLOR_BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const D3DXCOLOR OSGFCOLOR_YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR OSGFCOLOR_CYAN(0.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR OSGFCOLOR_MAGENTA(1.0f, 0.0f, 1.0f, 1.0f);

const D3DXCOLOR OSGFCOLOR_BEACH_SAND(1.0f, 0.96f, 0.62f, 1.0f);
const D3DXCOLOR OSGFCOLOR_LIGHT_YELLOW_GREEN(0.48f, 0.77f, 0.46f, 1.0f);
const D3DXCOLOR OSGFCOLOR_DARK_YELLOW_GREEN(0.1f, 0.48f, 0.19f, 1.0f);
const D3DXCOLOR OSGFCOLOR_DARKBROWN(0.45f, 0.39f, 0.34f, 1.0f);

inline D3DXVECTOR3 DXVecFromBullet(const btVector3& vec)
{
	return D3DXVECTOR3(vec.x(),vec.y(),vec.z());
}
inline btVector3 BulletVecFromDX(const D3DXVECTOR3& vec)
{
	return btVector3(vec.x,vec.y,vec.z);
}
inline D3DXQUATERNION DXQuatFromBullet(const btQuaternion& q)
{
	return D3DXQUATERNION(q.x(),q.y(),q.z(),q.w());
}
inline btQuaternion BulletQuatFromDX(const D3DXQUATERNION& q)
{
	return btQuaternion(q.x,q.y,q.z,q.w);
}


