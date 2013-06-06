#pragma once
#include "OSGFProjectile.h"
#include "OSGFShipComponent.h"
class OSGFShipTurret
	:public OSGFShipComponent
{
public:
	OSGFShipTurret(Game& game,OSGFPhysicsWorld& world,OSGFShip& ship)
		:OSGFShipComponent(game,world,ship)
	{

	}
	OSGFShipTurret(Game& game,OSGFPhysicsWorld& world,OSGFShip& ship,const btVector3& pos,
		const btVector3& dir)
		: OSGFShipComponent(game,world,ship,pos,dir)
	{

	}
	void FireTurret()
	{
		OSGFProjectile p(mGame,mWorld);
		
	}
};