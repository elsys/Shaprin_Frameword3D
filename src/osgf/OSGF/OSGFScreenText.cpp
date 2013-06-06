#include "OSGFScreenText.h"
#include "Util.h"
using namespace std;
OSGFScreenText::OSGFScreenText(Game& game)
	:OSGF2DDrawableComponent(game),
	mFont(NULL),mColor(NULL)
{
}
OSGFScreenText::OSGFScreenText(const OSGFScreenText& text)
	:OSGF2DDrawableComponent(text)
{
	Copy(text);
}
void OSGFScreenText::Initialize()
{
	if(IsInitialized())return;
	OSGFDrawableComponent::Initialize();
	if(!mColor)
		SetColor(0,0,0,1);
	InitFont();
}
void OSGFScreenText::SetFontDesc(const D3DX10_FONT_DESC& font)
{
	ReleaseCom(mFont);
	this->CreateFont(font);
}
void OSGFScreenText::Render()const
{
	mFont->DrawTextA(NULL,mText.c_str(),-1,&const_cast<RECT&>(GetRect().ToRect()),
					DT_NOCLIP,(FLOAT*)mColor);
}
void OSGFScreenText::SetColor(float r,float g,float b,float a)
{
	SetColor(D3DXCOLOR(r,g,b,a));
}
void OSGFScreenText::SetColor(const D3DXCOLOR& c)
{
	SafeDelete(mColor);
	mColor = new D3DXCOLOR(c);
}
const D3DXCOLOR& OSGFScreenText::GetColor()const
{
	return *mColor;
}

void OSGFScreenText::Update(double deltaTime)
{
	OSGFDrawableComponent::Update(deltaTime);
}
void OSGFScreenText::CreateFont(const D3DX10_FONT_DESC& fontDesc)
{
	D3DX10CreateFontIndirect(mGame.GetDevice(),&fontDesc,&mFont);
}
void OSGFScreenText::InitPlasement()
{
		RECT rect;
		rect.top = 5;
		rect.left = 5;
		rect.bottom = 0;
		rect.right = 0;
		SetPlasement(rect);
}
void OSGFScreenText::InitFont()
{
	D3DX10_FONT_DESC font;
	font.Height = 24;
	font.Weight = 0;
	font.Weight = 0;
	font.MipLevels = 1;
	font.Italic = false;
	font.CharSet = DEFAULT_CHARSET;
	font.OutputPrecision = OUT_DEFAULT_PRECIS;
	font.Quality = DEFAULT_QUALITY;
	font.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	wcscpy_s(font.FaceName,L"Times New Roman");
	this->CreateFont(font);
}
void OSGFScreenText::Copy(const OSGFScreenText& t)
{
	SetPlasement(t.GetRect());
	SetColor(*t.mColor);
	mText = t.mText;
	D3DX10_FONT_DESC font;
	t.mFont->GetDesc(&font);
	ReleaseCom(mFont);
	this->CreateFont(font);
}
OSGFScreenText::~OSGFScreenText(void)
{
	ReleaseCom(mFont);
	SafeDelete(mColor);
}
