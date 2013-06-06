#pragma once
#include <map>
#include <string>
#include "Game.h"
#include "GameState.h"
#include "OSGFMenuItem.h"
typedef std::map<std::string,OSGFMenuItem*> MenuMap;
typedef MenuMap::const_iterator ConstMenuIterator ;
typedef MenuMap::iterator MenuIterator;
typedef std::pair<std::string,OSGFMenuItem*> MenuPair;
class OSGFMenu
	:public GameState
{
public:

	OSGFMenu(Game& game)
		:GameState(game)
	{
	}
	OSGFMenu(const OSGFMenu& m)
		:GameState(m),mItems(m.mItems)
	{
		mSelected=mItems.find(m.mSelected->first);
	}
	void AddItem(std::string name,const OSGFMenuItem& item);
	void RemoveItem(std::string name);
	void RemoveAllItems();
	OSGFMenuItem* GetActive()
	{
		return mSelected->second;
	}
	const MenuMap& GetItems()const
	{
		return mItems;
	}
	virtual void Load()
	{
		if(IsInitialized())
			return;
		GameState::Load();
		for(MenuIterator itr = mItems.begin();itr!=mItems.end();itr++)
		{
			DeActivate(itr);
		}
		mSelected = mItems.begin();
		if(mSelected!=mItems.end())
			Activate(mSelected);
	}
	void NextItem();
	void PrevItem();
	void UseActive()
	{
		mSelected->second->Invoke();
	}
	
	virtual void Render()const
	{
		GameState::Render();
		ConstMenuIterator itr = mItems.begin();
		for(;itr!=mItems.end();++itr)
		{
			itr->second->Render();
		}
		if(mCursor)
			mCursor->Render();
	}
	virtual void Update(double dTime)
	{
		GameState::Update(dTime);
		for(MenuIterator itr = mItems.begin();
			itr!=mItems.end();++itr)
		{
			itr->second->Update(dTime);
		}
	}
	virtual void HandleInput(double dTime)
	{
		const OSGFMouse& m = mGame.GetMouse();
		LONG x = m.GetX();
		LONG y = m.GetY();
		mCursor->SetPosition(x,y);
		for(MenuIterator itr = mItems.begin();itr!=mItems.end();++itr)
		{
			if(itr->second->IsPointInside(x,y))
				ChangeActive(itr);
		}
		if(m.IsButtonReleased(OSGF_LEFT_MOUSE_BUTTON))
			UseActive();
	}
	virtual void Initialize();
	virtual ~OSGFMenu(void)
	{
		for(MenuMap::iterator itr = mItems.begin();itr!=mItems.end();itr++)
		{
			SafeDelete(itr->second);
		}
	}
	void SetCursor(OSGF2DDrawableComponent* cursor)
	{
		mCursor = cursor;
	}
private:
	static void Activate(const MenuIterator &itr)
	{
		itr->second->Activate();
	}
	static void DeActivate(const MenuIterator &itr)
	{
		itr->second->DeActivate();
	}
	void ChangeActive(const MenuIterator &itr)
	{
		DeActivate(mSelected);
		mSelected = itr;
		Activate(itr);
	}
	MenuMap mItems;
	MenuIterator mSelected;
	OSGF2DDrawableComponent* mCursor;
};

