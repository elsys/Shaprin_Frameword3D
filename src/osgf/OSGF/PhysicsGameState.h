#pragma once
#include <btBulletDynamicsCommon.h>
#include "OSGFLevel.h"
#include "OSGFCube.h"
#include "OSGFPlane.h"
#include "OSGFObjMeshLoader.h"
#include "OSGFPhysicsWorld.h"
#include "OSGFDrawablePhysicsBody.h"
#include "OSGFShip.h"
class PhysicsGameState
	:public OSGFLevel
{
public:
	PhysicsGameState(Game& game)
		:OSGFLevel(game),mShip(NULL)
	{
		
	}
	virtual void Initialize();
	virtual void HandleInput(double dTime);
	virtual void Render()const;
	virtual void Load();
	virtual void Update(double dTime);
	~PhysicsGameState();
private:
	void InitPhysics();
	void ClearPhysics();
	void InitGraphycs();
	void InitCammera();
	OSGFPhysicsWorld* mWorld;
	OSGFShip* mShip;
	OSGFDrawablePhysicsBody* mPlanet;
};