#include "PhysicsGameState.h"
#include "OSGFObjMeshLoader.h"
#include "OSGFShip.h"
#include "OSGFBoundCamera.h"
#include "OSGFFreeCamera.h"
#include "OSGFObjMeshLoader.h"
void PhysicsGameState::Initialize()
{
	if(IsInitialized())return;
		OSGFLevel::Initialize();
	mWorld = new OSGFPhysicsWorld(mGame);
	InitPhysics();
	SetClearColor(D3DXCOLOR(0,0,0,1));
	InitGraphycs();
}
void PhysicsGameState::InitPhysics()
{
	mWorld->Initialize();
	btCollisionShape* fallShape = new btBoxShape(btVector3(1,1,1));
	btCollisionShape* sphere = new btSphereShape(1);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
    btDefaultMotionState* fallMotionState =
                new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,20,0)));
	mShip = new OSGFShip(mGame,*mWorld);
	mShip->SetCollisionShape(fallShape);
	mShip->SetMotionState(fallMotionState);
	mShip->SetMass(1);
	mShip->Initialize();
	mPlanet = new OSGFDrawablePhysicsBody(mGame,*mWorld);
	mPlanet->SetMotionState(new btDefaultMotionState());
	mPlanet->SetCollisionShape(sphere);
	mPlanet->SetMass(0);
	mPlanet->Initialize();
}
void PhysicsGameState::InitGraphycs()
{
	SetLight(0.1f,0.1f,2.0f,0.5f,0.5f,0.8f,1.0f,1.0f,1.0f,0.0f,0.0f,+10.0f);
	SetClearColor(D3DXCOLOR(0.1f,0.1f,0.3f,1.0f));
	//mCamera.SetPosition(D3DXVECTOR3(0,35,-35));
	OSGFObjMeshLoader l(mGame,"../Content/Models/ship2.obj");
	l.Initialize();
	OSGFMesh* mesh = l.GetMesh("../Content/LightAndTexture.fx","LightAndTexture");
	InitCammera();
	mShip->SetDrawData(mesh);
	mShip->SetScaling(1,1,1);
	mShip->SetFrontLocal(D3DXVECTOR3(0,0,1));
	mShip->SetUpLocal(D3DXVECTOR3(-1,0,0));
	mShip->SetCamera(mCamera);
	mShip->SetLight(&GetLight());
	mShip->SetSpeed(0.01f);
	//mShip->SetEngine(OSGFShip::REAR_LEFT_DOWN,btVector3(5,5,5),btVector3(0,0,-1));
	mShip->SetEngine(0,btVector3(0,0,0),btVector3(1,0,0));
	mShip->SetEngine(1,btVector3(0,0,0),btVector3(-1,0,0));
	l.LoadFile("../Content/Models/sphere.obj");
	mPlanet->SetDrawData(l.GetMesh("../Content/monoColor.fx","MonoColorTech"));
	mPlanet->SetScaling(1,1,1);
	mPlanet->SetCamera(mCamera);
	mPlanet->SetLight(&GetLight());
}
void PhysicsGameState::InitCammera()
{
	OSGFBoundCamera cam(mGame,mShip);
	cam.SetFarPlane(1000);
	cam.SetNearPlane(1);
	cam.SetFovY((float)D3DX_PI*0.33);
	cam.SetLookAt(D3DXVECTOR3(0,3.50,-3.50),D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,1,0));
	cam.Initialize();
	SetCamera(cam);
}
void PhysicsGameState::Load()
{
	if(IsLoaded())
		return;
	if(mCamera)
		mCamera->OnScreenResize();
}
void PhysicsGameState::HandleInput(double dTime)
{
	const OSGFKeyboard& k = mGame.GetKeyboard();
	if(k.IsKeyReleased(VK_ESCAPE))
		mGame.SetActiveState("mainMenu");
	if(k.IsKeyDown(VK_SPACE))
	{
		mShip->GetRigidBody()->activate();
		mShip->RunEngine(0);
	}
	if(k.IsKeyDown(VK_CONTROL))
	{
		mShip->GetRigidBody()->activate();
		mShip->RunEngine(1);
	}
}
void PhysicsGameState::Render()const
{
	OSGFLevel::Render();
	mShip->Render();
	mPlanet->Render();
}
void PhysicsGameState::Update(double dTime)
{
	OSGFLevel::Update(dTime);  
	mWorld->Update(dTime);
	mShip->Update(dTime);
	mPlanet->Render();
	mCamera->Update(dTime);
}
PhysicsGameState::~PhysicsGameState()
{
	SafeDelete(mWorld);
	if(mShip)
	{
		SafeDelete(mShip->GetCollisionShape());
		delete mShip;
	}

}