#pragma once
#include <exception>
#include "IDrawable.h"
#include "OSGFDrawableComponent.h"
#include "OSGFComponentContainer.h"
class OSGFDrawableComponentContainer
	:public OSGFComponentContainer,IDrawable
{
public:
	virtual void Render()const
	{
		for(ContainerMapConstIterator itr = mComponents.cbegin();
			itr!=mComponents.end();itr++)
		{
			reinterpret_cast<OSGFDrawableComponent*>(itr->second)->Render();
		}
	}
	virtual void Add(std::string key,OSGFComponent* component)
	{
		if(dynamic_cast<OSGFDrawableComponent*>(component)==NULL)
			throw std::exception("inalid type");
		OSGFComponentContainer::Add(key,component);
	}

};