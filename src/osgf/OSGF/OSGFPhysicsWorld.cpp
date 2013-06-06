#include "OSGFPhysicsWorld.h"
void OSGFPhysicsWorld::Update(double dTime)
{
	mPhysicsWorld->stepSimulation(dTime);
}
void OSGFPhysicsWorld::Initialize()
{
	OSGFComponent::Initialize();
	mBroadphase = new btDbvtBroadphase();
 
    mCollisionConfiguration = new btDefaultCollisionConfiguration();
    mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
 
    mSolver = new btSequentialImpulseConstraintSolver;
 
    mPhysicsWorld = new btDiscreteDynamicsWorld(mDispatcher,mBroadphase,mSolver,mCollisionConfiguration);
	mPhysicsWorld->setGravity(btVector3(0,0,0));
 
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
    btDefaultMotionState* fallMotionState =
            new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,20,0)));
}
void OSGFPhysicsWorld::ApplyGravity(btRigidBody* b)
{
	btVector3 res(0,0,0);
	for(std::list<GravitationCenter>::iterator itr = mGravityCenters.begin();
		itr!=mGravityCenters.end();itr++)
	{
		res+=itr->CalculateForse(*b); 
	}
	b->applyCentralForce(res);
}