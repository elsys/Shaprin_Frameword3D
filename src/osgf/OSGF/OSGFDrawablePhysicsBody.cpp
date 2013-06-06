#include "OSGFDrawablePhysicsBody.h"
#include "OSGFPhysicsWorld.h"
OSGFDrawablePhysicsBody::OSGFDrawablePhysicsBody(Game& game,OSGFPhysicsWorld& world)
		:OSGF3DDrawableComponent(game),mShape(NULL),mMass(0.0f),
		mWorld(world),mBody(NULL)
{
	mMotionState = new btDefaultMotionState();
}
void OSGFDrawablePhysicsBody::Initialize()
{
		if(IsInitialized())return
		OSGF3DDrawableComponent::Initialize();
		mBody = new btRigidBody(mMass,mMotionState,mShape);
		mWorld.AddToWord(*this);
}
void OSGFDrawablePhysicsBody::Update(double dTime)
{
	btQuaternion q = 
		mMotionState->m_graphicsWorldTrans.getRotation();
	OSGF3DDrawableComponent::SetRotation(DXQuatFromBullet(q));
	btVector3 v =
		mMotionState->m_graphicsWorldTrans.getOrigin();
	OSGF3DDrawableComponent::SetTranslation(v.x(),v.y(),v.z());
	v = mBody->getCollisionShape()->getLocalScaling();
	OSGF3DDrawableComponent::SetScaling(v.x(),v.y(),v.z());
	OSGF3DDrawableComponent::Update(dTime);
	mDrawData->SetScaling(GetScaling());
	mDrawData->SetRotation(GetRotationMatrix());
	mDrawData->SetTranslation(GetTranslation());
	mDrawData->Update(dTime);
	mWorld.ApplyGravity(mBody);
}
void OSGFDrawablePhysicsBody::Render()const
{
	OSGF3DDrawableComponent::Render();
	
	mDrawData->Render();
}
void OSGFDrawablePhysicsBody::SetRotation(const D3DXMATRIX& m)
{
	btQuaternion q;
	double T = m[0] + m[5] + m[10] + 1;
	double S = 0.5/sqrt(T);
	if(T>0)
	{		
		q.setX((m[9]-m[6])*S);
		q.setY((m[2]-m[8])*S);
		q.setZ((m[4]-m[1])*S);
		q.setW(0.25/S);
	}
	else
	{
		float a[4] =
		{
			0.5/S,
			(m[1]+m[4])/S,
			(m[2]+m[8])/S,
			(m[6]+m[9])/S
		};
		if(m[0]>m[5]&&m[0]>m[10])
		{
			q.setX(a[0]);
			q.setY(a[1]);
			q.setZ(a[2]);
			q.setW(a[3]);
		}
		else if(m[5]>0&&m[5]>10)
		{
			q.setX(a[1]);
			q.setY(a[0]);
			q.setZ(a[3]);
			q.setW(a[2]);
		}
		else
		{
			q.setX(a[2]);
			q.setY(a[3]);
			q.setZ(a[0]);
			q.setX(a[1]);
		}
	}
	SetRotation(q);
}
OSGFDrawablePhysicsBody::~OSGFDrawablePhysicsBody()
{
	
	if(mBody)
	{
		mWorld.RemoveFromWorld(*this);
		delete mBody;
	}
	SafeDelete(mMotionState);
	SafeDelete(mDrawData);
}
