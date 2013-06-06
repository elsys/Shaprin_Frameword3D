#pragma once
#include <map>
#include <string>
#include "OSGFComponentContainer.h"
class OSGFComponentManager :
	public OSGFComponentContainer
{
public:
	OSGFComponentManager(Game& game);
	virtual void Initialize()
	{
		if(IsInitialized())return;
		OSGFComponentContainer::Initialize();	
	}
	virtual OSGFComponentManager* Clone()const
	{
		return new OSGFComponentManager(*this);
	}
	virtual void Update(double deltaTime);
	virtual void SetActive(std::string key);
	const OSGFComponent* GetActive() const
	{
		return mActive;
	}
	OSGFComponent* GetActive()
	{
		return mActive;
	}
	virtual ~OSGFComponentManager(void);
protected:
	OSGFComponent* mActive;
};

