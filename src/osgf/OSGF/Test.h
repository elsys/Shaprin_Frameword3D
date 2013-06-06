#pragma once
#include "game.h"
#include "OSGFScreenText.h"
#include "OSGFDrawableComponentManager.h"
#include "OSGFFreeCamera.h"
#include "OSGFCube.h"
#include "MainGameState.h"
#include "OSGFMenu.h"
#include "MainMenuState.h"
#include "PhysicsGameState.h"
class Test :
	public Game
{
public:
	Test(HINSTANCE hInstance,int nShowCmd,std::wstring aName,
		int aWidth,int aHeight);
	virtual void Initialize();
	virtual ~Test(void);
protected:
	virtual void Render();
	virtual void OnResize(WPARAM wParam,LPARAM lParam);
private:
	MainGameState* mainGame;
	MainMenuState* mainMenu;
	PhysicsGameState* physicGame;
	OSGFScreenText* mCursor;
};
