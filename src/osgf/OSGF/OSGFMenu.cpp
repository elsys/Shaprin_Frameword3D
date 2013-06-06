#include "OSGFMenu.h"
	void OSGFMenu::AddItem(std::string name,const OSGFMenuItem& item)
	{
		mItems.insert(MenuPair(name,new OSGFMenuItem(item)));
		if(mItems.size()==1)mSelected = mItems.begin();
	}
	void OSGFMenu::RemoveItem(std::string name)
	{
		if(name==mSelected->first)
		{
			if(mItems.begin()->first != name)
				mSelected = mItems.begin();
			else if(mItems.end()->first !=name)
				mSelected = mItems.end();
		}
		mItems.erase(name);
	}
	void OSGFMenu::RemoveAllItems()
	{
		mItems.clear();
	}
	void OSGFMenu::PrevItem()
	{
		DeActivate(mSelected);
		++mSelected;
		if(mSelected == mItems.end())
		{
			mSelected = mItems.begin();
		}
		Activate(mSelected);
	}
	void OSGFMenu::NextItem()
	{
		DeActivate(mSelected);
		if(mSelected==mItems.begin())
		{
			mSelected = mItems.end();	
		}
		--mSelected;
		Activate(mSelected);
	}
	
	void OSGFMenu::Initialize()
	{
		if(IsInitialized())
			return;
		GameState::Initialize();
		for(ConstMenuIterator itr = mItems.begin();
			itr!=mItems.end();++itr)
		{
			OSGFMenuItem* item = itr->second;
			if(!item->IsInitialized())
				item->Initialize();
		}
		if(!IsInitialized())
			GameState::Initialize();
	}