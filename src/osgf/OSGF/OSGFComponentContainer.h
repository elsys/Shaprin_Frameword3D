#pragma once
#include<map>
#include<string>
#include "OSGFComponent.h"
class OSGFComponentContainer
	:public OSGFComponent
{
public:
	OSGFComponentContainer(Game&game)
		:OSGFComponent(game)
	{

	}
	virtual OSGFComponentContainer* Clone()const
	{
		return new OSGFComponentContainer(*this);
	}
	virtual void Update(double dTime)
	{
		for(ContainerMapIterator itr = mComponents.begin();
			itr!=mComponents.end();itr++)
		{
			itr->second->Update(dTime);
		}
	}
	virtual void Initialize()
	{
		if(IsInitialized())
			return;
		OSGFComponent::Initialize();
	}
	virtual void Add(std::string key,OSGFComponent* component)
	{
		mComponents.insert(std::pair<std::string,OSGFComponent*>(key,component));
	}
	void Erase(std::string key)
	{
		mComponents.erase(key);
	}
	void DeleteComponent(std::string key)
	{
		delete mComponents[key];
		Erase(key);
	}
	void DeleteAllComponents()
	{
		for(ContainerMapIterator itr = mComponents.begin();
			itr!=mComponents.end();itr++)
		{
			delete itr->second;
		}
		mComponents.clear();
	}
	const OSGFComponent* Get(std::string key)
	{
		return mComponents.at(key);
	}
	virtual ~OSGFComponentContainer(void)
	{

	}
protected:
	typedef std::map<std::string,OSGFComponent*> ContainerMap;
	typedef ContainerMap::iterator ContainerMapIterator;
	typedef ContainerMap::const_iterator ContainerMapConstIterator;
	ContainerMap mComponents;
};

