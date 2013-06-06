#pragma once
#include <list>
#include "OSGFDrawablePhysicsBody.h"
class OSGFPhysicsWorld
	:public OSGFComponent
{
	class GravitationCenter
	{
	public:
		GravitationCenter(double mass, const btVector3 &p)
			:mMass(mass),mPos(p)
		{

		}
		GravitationCenter()
			:mMass(0),mPos()
		{

		}
		void SetPos(const btVector3& pos)
		{
			mPos = pos;
		}
		void SetMass(double mass)
		{
			mMass = mass;
		}
		btVector3 GetPos()const
		{
			return mPos;
		}
		long double GetMass()const
		{
			return mMass;
		}
		btVector3 CalculateForse(const btRigidBody& b)
		{
			btVector3 res = mPos-b.getWorldTransform().getOrigin();
			btScalar dist = res.length();
			res *= mMass/(dist*dist);
			return btVector3();
		}
	private:
		btVector3 mPos;
		float mMass;
	};
public:
	OSGFPhysicsWorld(Game& game)
		:OSGFComponent(game)
	{
	}
	void AddToWord(OSGFDrawablePhysicsBody& p)
	{
		mPhysicsWorld->addRigidBody(p.GetRigidBody());
	}
	void RemoveFromWorld(OSGFDrawablePhysicsBody& p)
	{
		mPhysicsWorld->removeRigidBody(p.GetRigidBody());
	}
	btDiscreteDynamicsWorld* GetWorld()
	{
		return mPhysicsWorld;
	}
	void AddGravityCenter(double mass,const btVector3& pos)
	{
		mGravityCenters.push_back(GravitationCenter(mass,pos));
	}
	~OSGFPhysicsWorld()
	{
		SafeDelete(mPhysicsWorld);
		SafeDelete(mSolver);
		SafeDelete(mCollisionConfiguration);
		SafeDelete(mDispatcher);
		SafeDelete(mBroadphase);
	}
	void ApplyGravity(btRigidBody* b);
	virtual void Update(double dTime);
	virtual void Initialize();
private:
	std::list<GravitationCenter> mGravityCenters;
	btDiscreteDynamicsWorld* mPhysicsWorld;
	btSequentialImpulseConstraintSolver* mSolver;
	btDefaultCollisionConfiguration* mCollisionConfiguration;
	btCollisionDispatcher* mDispatcher;
	btBroadphaseInterface* mBroadphase;
};