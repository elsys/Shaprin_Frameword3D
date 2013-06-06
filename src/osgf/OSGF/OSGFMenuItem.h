#pragma once
#include "IDrawable.h"
#include "Util.h"
#include "Rectangle.h"
class OSGFMenu;
class OSGFMenuItem;
typedef void(OSGFMenu::*OSGFMenuCommand)(OSGFMenuItem*);
typedef int (OSGFMenuItem::*FNMETHOD) ( int, char* );
class OSGFMenuItem:
	public OSGF2DDrawableComponent
{
public:
	OSGFMenuItem(Game& game,OSGFMenu& menu)
		:OSGF2DDrawableComponent(game),mMenu(menu),mActive(false)
	{
	}
	OSGFMenuItem(const OSGFMenuItem& menuItem)
		:OSGF2DDrawableComponent(menuItem),mMenu(menuItem.mMenu)
	{
		Copy(menuItem);
	}
	virtual OSGFMenuItem* Clone()const
	{
		return new OSGFMenuItem(*this);
	}
	OSGFMenuItem& operator=(const OSGFMenuItem& menuItem)
	{
		if(&menuItem != this)
			Copy(menuItem);
		return *this;
	}
	void SetActive(bool active)
	{
		mActive = active;
	}
	void Activate()
	{
		SetActive(true);
	}
	void DeActivate()
	{
		SetActive(false);
	}
	void SetCommand(OSGFMenuCommand command)
	{
		mCommand = command;
	}
	virtual void SetRectangle(const util::Rectangle& rect)
	{
		OSGF2DDrawableComponent::SetRectangle(rect);
		mDrawData->SetRectangle(rect);
		mActiveDrawData->SetRectangle(rect);
	}
	virtual void Render()const
	{
		if(!mActive)
			DrawIfNotNull(mDrawData);
		else
			if(!DrawIfNotNull(mActiveDrawData))
				DrawIfNotNull(mDrawData);

	}
	virtual void Update(double dTime)
	{
		OSGFDrawableComponent* drawData = 
			dynamic_cast<OSGFDrawableComponent*>(mDrawData);
		if(drawData)
			drawData->Update(dTime);
	}
	void Invoke()
	{
		(mMenu.*mCommand)(this);
	}
	~OSGFMenuItem()
	{
		SafeDelete(mDrawData);
		SafeDelete(mActiveDrawData);
	}
	void SetDrawData(OSGF2DDrawableComponent* drawData)
	{
		mDrawData = drawData;
	}
	void SetActiveDrawData(OSGF2DDrawableComponent* drawData)
	{
		mActiveDrawData = drawData;
	}
	
private:
	bool DrawIfNotNull(IDrawable* drawData)const
	{
		if(!drawData)return false;
		drawData->Render();
		return true;
	}
	void Copy(const OSGFMenuItem& menuItem)
	{
		mCommand = menuItem.mCommand;
		mDrawData = dynamic_cast<OSGF2DDrawableComponent*>( menuItem.mDrawData->Clone());
		mActiveDrawData = dynamic_cast<OSGF2DDrawableComponent*>(menuItem.mActiveDrawData->Clone());
		mActive = menuItem.mActive;
	}
	OSGFMenuCommand mCommand;
	OSGFMenu& mMenu;
	OSGF2DDrawableComponent* mDrawData;
	OSGF2DDrawableComponent* mActiveDrawData;
	bool mActive;
};

