#pragma once
#include <list>
#include "OSGFProjectile.h"
#include "OSGFComponent.h"
#include "EventSystem.h"
class OSGFProjectileSystem
	:public OSGFComponent
{
	typedef std::list<OSGFProjectile> ProjectileList;
	typedef ProjectileList::iterator ProjectileIterator;
public:
	virtual void Update(double dTime)
	{
		for(ProjectileIterator itr = mProjs.begin(); itr!=mProjs.end(); ++itr)
		{
			itr->Update(dTime);
			if(itr->GetTimeToLive()<=0)
				mProjs.erase(itr);
		}
	}
	void PutProjectile(const OSGFProjectile& proj)
	{
		mProjs.push_back(proj);
	}
private:
	ProjectileList mProjs;
};