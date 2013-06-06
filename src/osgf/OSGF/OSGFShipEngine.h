#pragma once
#include "OSGFShipComponent.h"
class OSGFShipEngine
	:public OSGFShipComponent
{
public:
	OSGFShipEngine(Game& game, OSGFPhysicsWorld& world,OSGFShip& ship)
		:OSGFShipComponent(game,world,ship)
	{

	}
	OSGFShipEngine(Game& game, OSGFPhysicsWorld& world,OSGFShip& ship,const btVector3& pos,
		const btVector3& dir)
		: OSGFShipComponent(game,world,ship,pos,dir)
	{

	}
	void RunEngine(float f);
};