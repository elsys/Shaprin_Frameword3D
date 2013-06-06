#pragma once
#include "OSGFPhysicsWorld.h"
#include "OSGFDrawablePhysicsBody.h"
class OSGFProjectile
	:public OSGFDrawablePhysicsBody
{
public:
	OSGFProjectile(Game& game,OSGFPhysicsWorld& world)
		:OSGFDrawablePhysicsBody(game,world)
	{

	}
	virtual void Update(double dTime)
	{
		OSGFDrawablePhysicsBody::Update(dTime);
		mTTL-=dTime;
	}
	void SetTimeToLive(double time)
	{
		mTTL = time;
	}
	double GetTimeToLive()const 
	{
		return mTTL;
	}
	
private:
	double mTTL;
};
