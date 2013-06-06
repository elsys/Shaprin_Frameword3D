#include "Game.h"
#include"OSGFComponent.h"
void OSGFComponent::SendMessage(UINT message,std::intptr_t arg1,std::intptr_t arg2)
{
		mGame.GetEventSystem().SendMessage(message,arg1,arg2);
}
UINT OSGFComponent::SetDispatcher(EventSystem::EventDispatcher* dispatcher)
{	
	return mGame.GetEventSystem().SetDispatcher(dispatcher);
}
void OSGFComponent::RemoveDispatcher(UINT message)
{
	mGame.GetEventSystem().RemoveDispatcher(message);
}