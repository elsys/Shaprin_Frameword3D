#pragma once
class OSGFShip;
#include "OSGFPhysicsWorld.h"
class OSGFShipComponent
	:public OSGFDrawablePhysicsBody
{
public:
	OSGFShipComponent(Game& game, OSGFPhysicsWorld& world, 
		OSGFShip& ship)
		:OSGFDrawablePhysicsBody(mGame,world),mShip(ship),mPos(),mDir()
	{

	}
	OSGFShipComponent(Game& game, OSGFPhysicsWorld& world,
		OSGFShip& ship,const btVector3& pos,
		const btVector3& dir)
		:OSGFDrawablePhysicsBody(game,world),mShip(ship),mPos(pos),mDir(dir)
	{

	}
	OSGFShipComponent(const OSGFShipComponent& c)
		:OSGFDrawablePhysicsBody(c.mGame,c.mWorld),mShip(c.mShip)
	{
		Copy(c);
	}
	OSGFShipComponent& operator=(const OSGFShipComponent& c)
	{
		if(this!=&c)
			Copy(c);
		return *this;
	}
	void SetPos(const btVector3& pos)
	{
		mPos = pos;
	}
	const btVector3& GetPos()const
	{
		return mPos;
	}
	void SetDirection(const btVector3& dir)
	{
		mDir = dir;
	}
	const btVector3& GetDirection()const
	{
		return mDir;
	}
	void SetForceAmount(btScalar n)
	{
		mDir.normalize()*=n;
	}
	btScalar GetForceAmount()const
	{
		return mDir.length();
	}
protected:
	void Copy(const OSGFShipComponent& comp)
	{
		mPos = comp.mPos;
		mDir = comp.mDir;
	}
	OSGFShip& mShip;
	btVector3 mPos;
	btVector3 mDir;

};