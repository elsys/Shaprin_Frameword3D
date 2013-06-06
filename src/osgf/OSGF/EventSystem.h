#pragma once
#include <cstdint>
#include <vector>
#include "Util.h"
class EventSystem
{
public:
	class EventDispatcher
	{
	public:
		virtual void DispatchEvent(std::intptr_t arg1,
			std::intptr_t arg2)=0;
		void operator()(std::intptr_t arg1,
			std::intptr_t arg2)
		{
			DispatchEvent(arg1,arg2);
		}
	private:
	};
	void SendMessage(UINT message, std::intptr_t arg1,
			std::intptr_t arg2)
	{
		EventDispatcher* d = mDispatchers[message];
		if(d)(*d)(arg1,arg2);
	}
	UINT SetDispatcher(EventDispatcher* dipatcher)
	{
		mDispatchers.push_back(dipatcher);
		return mDispatchers.size()-1;
	}
	void RemoveDispatcher(UINT message)
	{
		delete mDispatchers[message];
		mDispatchers[message] = NULL;
		mFreeMessageIds.push_back(message);
	}
private:
	std::vector<EventDispatcher*> mDispatchers;
	std::vector<UINT> mFreeMessageIds;
};