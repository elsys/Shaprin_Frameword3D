#include "OSGFComponentManager.h"
using namespace std;

OSGFComponentManager::OSGFComponentManager(Game& game)
	:OSGFComponentContainer(game), mActive(NULL)
{

}
void OSGFComponentManager::Update(double deltaTime)
{
	if(mActive)mActive->Update(deltaTime);
}

void OSGFComponentManager::SetActive(string key)
{
	mActive = mComponents[key];
	if(mActive == NULL)
	{
		throw key+" is not in the manager!";
	}
}
OSGFComponentManager::~OSGFComponentManager(void)
{
}

