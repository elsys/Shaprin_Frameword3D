#include "MainMenuState.h"
#include "Game.h"
#include "MenuText.h"
#include "Keyboard.h"
using namespace std;
void MainMenuState::OnMenuNewGame(OSGFMenuItem* item)
{
	mGame.SetActiveState("mainGame");
}
void MainMenuState::OnQuit(OSGFMenuItem* item)
{
	mGame.Quit();
}
void MainMenuState::OnMenuPhysicsTest(OSGFMenuItem* item)
{
	mGame.SetActiveState("physicsState");
}
void MainMenuState::Initialize()
{
	if(IsInitialized())return;
	OSGFMenu::Initialize();
	CreateButtons();
}
void MainMenuState::CreateButtons()
{
	int height = mGame.GetScreenHeight();
	int width = mGame.GetScreenWidth();
	CreateButton("• Quit",&MainMenuState::OnQuit,
		width/2,height/2+20,50,20);
	CreateButton("• PhysicsTest",&MainMenuState::OnMenuPhysicsTest,
		width/2,height/2,50,20);
	CreateButton("• New Game",&MainMenuState::OnMenuNewGame,
		width/2,height/2-20,50,20);
}
void MainMenuState::HandleInput(double dTime)
{
	OSGFMenu::HandleInput(dTime);
	const OSGFKeyboard& k = mGame.GetKeyboard();
	if(k.IsKeyReleased(VK_RETURN))
		UseActive();
	if(k.IsKeyReleased(VK_DOWN))
		this->PrevItem();
	if(k.IsKeyReleased(VK_UP))
		this->NextItem();
	if(k.IsKeyReleased(VK_ESCAPE))
		mGame.Quit();
	
}
void MainMenuState::OnScreenResize(WPARAM wParam,LPARAM lParam)
{
	RemoveAllItems();
	CreateButtons();
}
void MainMenuState::CreateButton(string name,OSGFMainMenuCommand action,
	int left,int top,int width,int height)
{
	MenuText menuText(mGame,*this);
	menuText.SetCommand(static_cast<OSGFMenuCommand>(action));
	menuText.SetText(name);
	menuText.SetColor(1,0,0,1);
	menuText.SetActiveDrawColor(1,1,0);
	menuText.Initialize();
	menuText.SetRectangle(util::Rectangle(left,top,width+left,height+top));
	AddItem(name,menuText);
}



