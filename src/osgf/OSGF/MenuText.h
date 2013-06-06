#pragma once
#include "Game.h"
#include "OSGFScreenText.h"
#include "osgfmenuitem.h"
class MenuText :
	public OSGFMenuItem
{
public:

	MenuText(Game& game,OSGFMenu& menu)
		:OSGFMenuItem(game,menu),text(game),activeText(game)
	{
	}
	MenuText(const MenuText& t)
		:OSGFMenuItem(t),activeText(t.activeText),text(t.text)
	{
	}
	MenuText& operator=(const MenuText& t)
	{
		if(this!=&t)
		{
			OSGFMenuItem::operator=(t);
			Copy(t);
		}
		return *this;
	}
	virtual MenuText* Clone()const
	{
		return new MenuText(*this);
	}
	virtual void Initialize()
	{
		if(IsInitialized())return;
		OSGFMenuItem::Initialize();
		text.Initialize();
		activeText.Initialize();
		SetDrawData(&text);
		SetActiveDrawData(&activeText);
	}
	void SetText(std::string str)
	{
		text.SetText(str);
		activeText.SetText(str);
	}
	void SetColor(const D3DXCOLOR& color)
	{
		text.SetColor(color);
	}
	void SetColor(float r,float g,float b,float a=1.0f)
	{
		text.SetColor(r,g,b,a);
	}
	void SetActiveDrawColor(const D3DXCOLOR& color)
	{
		activeText.SetColor(color);
	}
	void SetActiveDrawColor(float r,float g,float b,float a=1.0f)
	{
		activeText.SetColor(r,g,b,a);
	}
	virtual ~MenuText(void)
	{
	}
private:
	void Copy(const MenuText& t)
	{
		text = t.text;
		activeText = t.activeText;
	}
	OSGFScreenText text;
	OSGFScreenText activeText;
};

