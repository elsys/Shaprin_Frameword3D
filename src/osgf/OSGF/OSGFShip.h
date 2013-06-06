#pragma once
#include<map>
#include "OSGFShipEngine.h"
#include "OSGFShipTurret.h"
#include "OSGFDrawablePhysicsBody.h"
class OSGFShip
	:public OSGFDrawablePhysicsBody
{
	typedef std::map<std::string,OSGFShipTurret> Turrets;
	typedef std::pair<std::string,OSGFShipTurret> NameTurretPair;
public:
	enum
	{
		REAR_LEFT_UP,REAR_LEFT_DOWN,REAR_RIGHT_UP,REAR_RIGHT_DOWN,
		FRONT_LEFT_UP,FRONT_LEFT_DOWN,FRONT_RIGHT_UP,FRONT_RIGHT_DOWN,
		SIDE_LEFT,SIDE_RIGHT,
	};
	OSGFShip(Game& game,OSGFPhysicsWorld& world)
		:OSGFDrawablePhysicsBody(game,world),mSpeed(1.0f)
	{
		for(int i = 0;i<10;i++)
			mEngines[i] = new OSGFShipEngine(game,world,*this);
	}
	void SetEngine(UINT type, const btVector3 &pos,const btVector3& dir)
	{
		mEngines[type]->SetPos(pos);
		mEngines[type]->SetDirection(dir);
	}
	OSGFShipEngine& GetEngine(UINT type)
	{
		return *mEngines[type];
	}
	
	void RemoveEngine(UINT type)
	{
		mEngines[type]->SetDirection(btVector3(0,0,0));
	}
	void SetTurret(const std::string& key, const btVector3 &pos,const btVector3& dir)
	{
		//mTurrets.insert(NameTurretPair(key,OSGFShipTurret(mGame,mWorld,*this,pos,dir)));
	}
	OSGFShipTurret& GetTurret(const std::string& key)
	{
		//return mTurrets[key];
	}
	void RunEngine(UINT type)
	{
		mEngines[type]->RunEngine(mSpeed);
	}
	void FireTurret(std::string key)
	{
		//mTurrets[key].FireTurret();
	}
	float GetSpeed()const
	{
		return mSpeed;
	}
	void SetSpeed(float speed)
	{
		mSpeed = speed;
	}
	virtual ~OSGFShip()
	{
		for(int i = 0;i<10;i++)
			delete mEngines[i]; 
	}
private:
	OSGFShipEngine *mEngines[10];
	//Turrets mTurrets;
	UINT mLife;
	UINT mMaxLife;
	float mSpeed;
};