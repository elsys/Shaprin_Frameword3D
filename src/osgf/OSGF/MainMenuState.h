#pragma once
#include "osgfmenu.h"
#include "Util.h"
#include "OSGFMenuItem.h"
#include "OSGFScreenText.h"
class MainMenuState;
typedef void(MainMenuState::*OSGFMainMenuCommand)(OSGFMenuItem*);
class MainMenuState :
	public OSGFMenu
{
public:

	MainMenuState(Game& game)
		:OSGFMenu(game)
	{
	}
	MainMenuState(const MainMenuState& m)
		:OSGFMenu(m)
	{
	}
	virtual MainMenuState* Clone()const
	{
		return new MainMenuState(*this);
	}
	virtual void Initialize();
	virtual void HandleInput( double dTime);
	virtual void OnScreenResize(WPARAM wParam,LPARAM lParam);
	void OnMenuNewGame(OSGFMenuItem* item);
	void OnMenuPhysicsTest(OSGFMenuItem* item);
	void OnQuit(OSGFMenuItem* item);
	virtual ~MainMenuState(void)
	{
	
	}
private:
	void InitNewGame();
	void InitQuit();
	void InitPhysics();
	void CreateButton(std::string name,OSGFMainMenuCommand action,
		int x,int y,int widht,int height);
	void CreateButtons();
};

