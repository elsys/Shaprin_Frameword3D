#pragma once
class Game;
#include <cstdint>
#include <Windows.h>
#include "EventSystem.h"
class OSGFComponent
{
public:
	virtual void Initialize()
	{
		if(IsInitialized())return;
		mIsInitialized = true;
		Load();
	}
	virtual void Load()
	{
		mIsLoaded = true;
	}
	virtual OSGFComponent* Clone()const
	{
		return new OSGFComponent(*this);
	}
	virtual void Unload()
	{
		mIsLoaded = false;
	}
	virtual bool IsLoaded()
	{
		return mIsLoaded;
	}
	virtual void Update(double deltaTime) 
	{
			
	};
	virtual OSGFComponent& operator=(const OSGFComponent& c)
	{
		Copy(c);
		return *this;
	}
	virtual ~OSGFComponent(void){};
	bool IsInitialized()
	{
		return mIsInitialized;
	}
	Game& GetGame()
	{
		return mGame;
	}
protected:
	OSGFComponent(Game& game)
		:mGame(game),mIsLoaded(false),mIsInitialized(false)
	{}
	OSGFComponent(const OSGFComponent& component)
		:mGame(component.mGame)
	{
		Copy(component);
	}
	void SendMessage(UINT message,std::intptr_t arg1,std::intptr_t arg2);
	UINT SetDispatcher(EventSystem::EventDispatcher* dispatcher);
	void RemoveDispatcher(UINT message);
	Game& mGame;
private:
	void Copy(const OSGFComponent& c)
	{
		mIsInitialized = c.mIsInitialized;
		mIsLoaded = c.mIsLoaded;
	}
	bool mIsInitialized;
	bool mIsLoaded;
};

