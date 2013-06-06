#pragma once
#include "OSGFDrawableComponentManager.h"
#include "IDrawable.h"
#include "GameState.h"
class StateMachine :
	public OSGFDrawableComponentManager
{
public:
	StateMachine(Game& game)
		:OSGFDrawableComponentManager(game)
	{
	}
	void OnScreenResize(WPARAM wParam, LPARAM lParam)
	{
		const OSGFComponent* cc = GetActive();
		if(!cc)return;
		const GameState* cgs = dynamic_cast<const GameState*>(cc);
		GameState* gs = const_cast<GameState*>(cgs);
		gs->OnScreenResize(wParam,lParam);;
	}
	virtual void SetActive(std::string key)
	{
		if(mActive)mActive->Unload();
		OSGFComponentManager::SetActive(key);
		mActive->Initialize();
		mActive->Load();
	}
	~StateMachine(void)
	{
	}
};

