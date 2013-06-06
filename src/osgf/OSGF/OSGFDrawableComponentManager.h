#pragma once
#include "IDrawable.h"
#include "OSGFComponentManager.h"
class OSGFDrawableComponentManager
	:public OSGFComponentManager,public IDrawable
{
public:
	OSGFDrawableComponentManager(Game& game);
	OSGFDrawableComponentManager(const OSGFDrawableComponentManager& o)
		:OSGFComponentManager(o)
	{

	}
	virtual OSGFDrawableComponentManager* Clone()const
	{
		return new OSGFDrawableComponentManager(*this);
	}
	virtual void Render()const;
	virtual void Initialize();
	virtual void Update(double deltaTime);
	virtual void Add(std::string key,OSGFComponent* component);
	~OSGFDrawableComponentManager(void);
};

