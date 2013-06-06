#include "OSGFShipEngine.h"
#include "OSGFShip.h"
void OSGFShipEngine::RunEngine(float f)
{
	mShip.GetRigidBody()->applyForce(mDir*f,mPos);
}