#pragma once
#include "OSGF2DDrawableComponent.h"
#include <D3DX10.h>
#include <string>
#include "Game.h"
#include "Util.h"
class OSGFScreenText :
	public OSGF2DDrawableComponent
{
public:
	OSGFScreenText(Game& game);
	OSGFScreenText(const OSGFScreenText& text);
	virtual void Initialize();
	virtual void Render()const;
	void SetColor(float r = 0,float g = 0,float b = 0,float a = 1);
	void SetColor(const D3DXCOLOR& c);
	const D3DXCOLOR& GetColor()const; 
	void SetText(std::string aText)
	{
		mText = aText;
	}
	virtual OSGFScreenText* Clone()const
	{
		return new OSGFScreenText(*this);
	}
	void SetPlasement(const RECT&rect)
	{
		SetRectangle(rect);
	}
	OSGFScreenText& operator=(const OSGFScreenText& t)
	{
		if(this!=&t)
			Copy(t);
		return *this;
	}
	void SetPlasement(long top,long left,long bottom=0,long right=0)
	{
		RECT rect;
		rect.top = top;
		rect.left = left;
		rect.bottom = bottom;
		rect.right = right;
		SetPlasement(rect);
	}
	void SetFontDesc(const D3DX10_FONT_DESC& font);
	std::string GetText()const
	{
		return mText;
	}
	void Update(double deltaTime);
	virtual ~OSGFScreenText(void);
private:
	void Copy(const OSGFScreenText& t);
	void CreateFont(const D3DX10_FONT_DESC& fontDesc);
	void InitPlasement();
	void InitFont();
	std::string mText;
	ID3DX10Font* mFont;
	D3DXCOLOR* mColor;
};
