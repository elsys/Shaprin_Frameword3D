#include "OSGFDrawableComponentManager.h"
#include "MainGameState.h"
using namespace std;

OSGFDrawableComponentManager::OSGFDrawableComponentManager(Game& game)
	:OSGFComponentManager(game)
{

}
void OSGFDrawableComponentManager::Render()const
{
	dynamic_cast<const OSGFDrawableComponent*>(GetActive())->Render();
}
void OSGFDrawableComponentManager::Initialize()
{
	if(IsInitialized())return;
	OSGFComponentManager::Initialize();
}
void OSGFDrawableComponentManager::Update(double deltaTime)
{
	OSGFComponentManager::Update(deltaTime);
}
void OSGFDrawableComponentManager::Add(string key,OSGFComponent* component)
{
	OSGFComponentManager::Add(key,component);
}
OSGFDrawableComponentManager::~OSGFDrawableComponentManager(void)
{
}
