#include <sstream>
#include "MainGameState.h"
#include "Game.h"
#include "OSGFFreeCamera.h"
#include "Keyboard.h"
#include "OSGFObjMeshLoader.h"
using namespace std;
MainGameState::MainGameState(Game& game)
	:OSGFLevel(game)
{
	screenText1 = new OSGFScreenText(game);
	screenText2 = new OSGFScreenText(game);
	textManager = new OSGFDrawableComponentManager(game);
}
void MainGameState::Initialize()
{
	if(IsInitialized())
		return;
	OSGFLevel::Initialize();
	InitializeGraphics();
	IntializeLight();
	SetClearColor(D3DXCOLOR(0.2f,0.3f,0.5f,1));
}
void MainGameState::IntializeLight()
{
	SetLight(1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,
			1.0f,1.0f,1.0f,
			10.0f,10.0f,0.0f);
}
void MainGameState::InitializeGraphics()
{
	screenText1->Initialize();
	screenText2->Initialize();
	screenText1->SetColor(0.0f,0.7f,0.0f,1.0f);
	screenText2->SetColor(0.0f,0.7f,0.0f,1.0f);
	screenText2->SetText("Hello my friend,кефиш се на слънцето?");
	textManager->Initialize();
	textManager->Add("FPS info",screenText1);
	textManager->Add("Hello",screenText2);
	textManager->SetActive("FPS info");
	OSGFObjMeshLoader loader(mGame,"../Content/Models/ship2.obj");
	loader.Initialize();
	InitializeCamera();
	mMesh = loader.GetMesh("../Content/LightAndTexture.fx","LightAndTexture");
	mMesh->SetCamera(mCamera);
	mMesh->RotateY(D3DX_PI/2);
	mMesh->SetScaling(1.0f,1.0f,1.0f);
	mMesh->SetLight(&GetLight());
	mSkyBox = new OSGFSkyBox(mGame,"../Content/SkyBox.fx","SkyBoxTech");
	mSkyBox->SetCamera(mCamera);
	mSkyBox->Initialize();
	mSkyBox->SetTexture("D:/MyPrograms/osgf/Content/Models/Textures/stars-texture-3.jpg");
	mSkyBox->SetScaling(100,100,100);
}
void MainGameState::InitializeCamera()
{
	OSGFFreeCamera cam(mGame);
	cam.SetFarPlane(1000);
	cam.SetNearPlane(1);
	cam.SetFovY((float)D3DX_PI*0.33);
	cam.SetLookAt(D3DXVECTOR3(0,3.50,-3.50),D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,1,0));
	cam.Initialize();
	cam.OnScreenResize();
	SetCamera(cam);
}
void MainGameState::Render()const
{
	GameState::Render();
	mMesh->Render();
	mSkyBox->Render();
	textManager->Render();
}
void MainGameState::Update(double dTime)
{
	OSGFLevel::Update(dTime);
	textManager->Update(dTime);
	ostringstream strs;
	strs<<"Time between frames:"<<dTime;
	strs<<"\nFPS:"<<1/dTime;
	strs<<"\nGameTime:"<<mGame.GetGameTime();
	screenText1->SetText(strs.str());
	mMesh->Update(dTime);
	mSkyBox->Update(dTime);
}
void MainGameState::HandleInput(double dTime)
{
	const OSGFKeyboard& k = mGame.GetKeyboard();
	OSGFFreeCamera* cam = static_cast<OSGFFreeCamera*>(mCamera);
	if(k.IsKeyReleased(VK_ESCAPE))
		mGame.GetStateMachine().SetActive("mainMenu");
	if(k.IsKeyReleased('H'))
		textManager->SetActive("Hello");
	if(k.IsKeyReleased('J'))
		textManager->SetActive("FPS info");
	if(k.IsKeyDown(VK_UP))
		cam->MoveForward();
	if(k.IsKeyDown(VK_DOWN))
		cam->MoveBack();
	if(k.IsKeyDown(VK_LEFT))
		cam->MoveLeft();
	if(k.IsKeyDown(VK_RIGHT))
		cam->MoveRight();
	if(k.IsKeyDown(VK_SPACE))
		cam->MoveUp();
	if(k.IsKeyDown(VK_CONTROL))
		cam->MoveDown();
	if(k.IsKeyDown('W'))
		mMesh->RotateX(0.01f*dTime);
	if(k.IsKeyDown('S'))
		mMesh->RotateX(-0.01f*dTime);
	if(k.IsKeyDown('A'))
		mMesh->RotateY(-0.01f*dTime);
	if(k.IsKeyDown('D'))
		mMesh->RotateY(0.01f*dTime);
	if(k.IsKeyDown('Q'))
		mMesh->RotateZ(-0.01f*dTime);
	if(k.IsKeyDown('E'))
		mMesh->RotateZ(0.01f*dTime);
	if(k.IsKeyDown(VK_NUMPAD8))
		mMesh->Move(0,0,0.01f*dTime);
	if(k.IsKeyDown(VK_NUMPAD2))
		mMesh->Move(0,0,-0.01f*dTime);

}
void MainGameState::Load()
{
	if(IsLoaded())return;
	if(!IsInitialized())Initialize();
	OSGFLevel::Load();
	if(mCamera)
		mCamera->OnScreenResize();
}
void MainGameState::Unload()
{
	if(!IsLoaded())return;
	OSGFLevel::Unload();
	SafeDelete(screenText1);
	SafeDelete(screenText2);
	SafeDelete(textManager);
	SafeDelete(mMesh);
}
MainGameState::~MainGameState(void)
{
	Unload();
}
