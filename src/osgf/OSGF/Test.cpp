#include "Test.h"
#include <cstring>
#include <sstream>
#include "OSGFObjMeshLoader.h"
#include "Util.h"
#include <iostream>
using namespace std;
#undef DEBUG
#undef _DEBUG
Test::Test(HINSTANCE hInstance,int nShowCmd,std::wstring aName,
		int aWidth,int aHeight)
		:Game(hInstance,nShowCmd,aName,aWidth,aHeight),mainGame(NULL)
{
	
}
void Test::Initialize()
{	
	Game::Initialize();
#if defined(DEBUG) || defined(_DEBUG)
	SetScreenSize(800,600);
	SetFullScreen(false);
#else
	SetScreenSize(1280,1024);
	SetFullScreen(true);
#endif
	mCursor = new OSGFScreenText(*this);
	mCursor->Initialize();
	mCursor->SetColor(1.0f);
	mCursor->SetPlasement(100,100);
	mCursor->SetText("X");
	mainGame = new MainGameState(*this);
	AddState("mainGame",mainGame);
	mainMenu = new MainMenuState(*this);
	mainMenu->SetCursor(mCursor);
	AddState("mainMenu",mainMenu);
	physicGame = new PhysicsGameState(*this);
	AddState("physicsState",physicGame);
	mainMenu->SetCursor(mCursor);
	SetActiveState("mainMenu");
}

void Test::Render()
{
	GetStateMachine().Render();
	Present();
}
void Test::OnResize(WPARAM wParam,LPARAM lParam)
{
	Game::OnResize(wParam,lParam);
}

Test::~Test(void)
{
	GetStateMachine().DeleteAllComponents();
	SafeDelete(mCursor);
}
