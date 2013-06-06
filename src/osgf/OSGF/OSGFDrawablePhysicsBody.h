#pragma once
#include <exception>
#include <btBulletDynamicsCommon.h>
#include "OSGF3DDrawableComponent.h"
class OSGFPhysicsWorld;
class OSGFDrawablePhysicsBody 
	:public OSGF3DDrawableComponent
{
public:
	OSGFDrawablePhysicsBody(Game& game,
		OSGFPhysicsWorld& world);
	virtual void Update(double dTime);
	virtual void Render()const;
	virtual void Initialize();
	virtual void SetTranslation(float x,float y,float z)
	{
		SetTranslation(btVector3(x,y,z));
	}
	virtual void SetTranslation(const D3DXVECTOR3& v)
	{
		SetTranslation(v.x,v.y,v.z);
	}
	virtual void SetTranslation(const D3DXMATRIX& m)
	{
		SetTranslation(m._41,m._42,m._43);
	}
	void SetTranslation(const btVector3 &v)
	{
		mPos = v;
		CreateMotionSatate();
	}
	virtual void SetScaling(float x,float y,float z)
	{
		SetScaling(btVector3(x,y,z));
	}
	void SetScaling(const btVector3& v)
	{
		mShape->setLocalScaling(v);
		CalculateInertia();
		mBody->setCollisionShape(mShape);
	}
	virtual void SetScaling(const D3DXVECTOR3& v)
	{
		SetScaling(v.x,v.y,v.z);
	}
	virtual void SetScaling(const D3DXMATRIX& m)
	{
		SetScaling(m._11,m._22,m._33);
	}
	virtual void SetRotation(float x,float y,float z)
	{
		SetRotation(btQuaternion(y,x,z));
	}
	void SetRotation(const btQuaternion &q)
	{
		mRotation = q;
		CreateMotionSatate();
	}
	virtual void SetRotation(const D3DXQUATERNION &q)
	{
		SetRotation(BulletQuatFromDX(q));
	}
	virtual void RotateX(float a)
	{
		btQuaternion b(0,a,0);
		SetRotation(mRotation * b);
	}
	virtual void RotateY(float a)
	{
		btQuaternion b(a,0,0);
		SetRotation(mRotation * b);
	}
	virtual void RotateZ(float a)
	{
		btQuaternion b(0,0,a);
		SetRotation(mRotation * b);
	}
	void SetMotionState(btDefaultMotionState* m)
	{
		SafeDelete(mMotionState);
		mMotionState = m;
	}
	btDefaultMotionState* GetMotionState()const
	{
		return mMotionState;
	}
	btRigidBody* GetRigidBody()
	{
		return mBody;
	}
	void SetDrawData(OSGF3DDrawableComponent* drawData)
	{
		mDrawData = drawData->Clone();
		if(GetLight())
			mDrawData->SetLight(GetLight());
		if(GetCamera())
			mDrawData->SetCamera(GetCamera());
	}
	const OSGF3DDrawableComponent* GetDrawData()const
	{
		return mDrawData;
	}
	virtual void SetCamera(const OSGFCamera* cam)
	{
		OSGF3DDrawableComponent::SetCamera(cam);
		if(mDrawData)
			mDrawData->SetCamera(cam);
	}
	virtual void SetLight(const Light* light)
	{
		OSGF3DDrawableComponent::SetLight(light);
		if(mDrawData)
			mDrawData->SetLight(light);
	}
	void SetMass(btScalar mass)
	{
		mMass = mass;
		CalculateInertia();
	}
	btScalar GetMass()const
	{
		return mMass;
	}
	virtual void SetRotation(const D3DXMATRIX& m);
	void SetCollisionShape(btCollisionShape* shape)
	{
		mShape = shape;
		CalculateInertia();
	}
	btCollisionShape* GetCollisionShape()
	{
		return mShape;
	}
	OSGFPhysicsWorld& GetPhysicsWorld()
	{
		return mWorld;
	}
	~OSGFDrawablePhysicsBody();
protected:
	OSGFPhysicsWorld & mWorld;
private:
	void CreateMotionSatate()
	{
		SafeDelete(mMotionState);
		mMotionState = new btDefaultMotionState(btTransform(mRotation,mPos));
		mBody->setMotionState(mMotionState);
	}
	void CalculateInertia()
	{
		mShape->calculateLocalInertia(mMass,mInertia);
	}
	btRigidBody* mBody;
	btCollisionShape* mShape;
	btDefaultMotionState* mMotionState;
	btQuaternion mRotation;
	btVector3 mPos;
	btVector3 mInertia;
	btScalar mMass;
	OSGF3DDrawableComponent* mDrawData;
};