#pragma once
#include <d3d10.h>
#include <D3DX10.h>
#include <string>
#include <map>
#include "GameTimer.h"
#include "OSGFScreenText.h"
#include "EventSystem.h"
#include "StateMachine.h"
#include "OSGFKeyboard.h"
#include "OSGFMouse.h"
#include "InputSystem.h"
class Game
{
public:
	Game(HINSTANCE hInstance,int nShowCmd,std::wstring aName,
		int aWidth,int aHeight,int aRefreshRate = 60);
	void Run();
	ID3D10Device* GetDevice()const
	{
		return mDevice;
	}
	LRESULT CALLBACK MsgProc(UINT msg,WPARAM wParam,LPARAM lParam);
	virtual void Initialize();
	double GetGameTime()const
	{
		return mGameTimer.GetGameTime();
	}
	bool IsFullScreen()const
	{
		return mFullScreen;
	}
	HWND GetWindowHandler()
	{
		return mhWnd;
	}
	HINSTANCE GetInstance()
	{
		return mhInstance;
	}
	void Quit()
	{
		SetFullScreen(false);
		PostMessage(mhWnd,WM_DESTROY,0,0);
	}
	void SetScreenSize(int widht,int height);
	int GetScreenWidth()const
	{
		return mWidth;
	}
	const OSGFKeyboard& GetKeyboard()const
	{
		return *mKeyboard;
	}
	const OSGFMouse& GetMouse()const
	{
		return *mMouse;
	}
	void ClearColorDephtStencil(D3DXCOLOR color,FLOAT depth=1.0f,UINT8 stencil=0)const;
	int GetScreenHeight()const
	{
		return mHeight;
	}
	StateMachine& GetStateMachine()
	{
		return *mStateMachine;
	}
	void Pause();
	void Unpause();
	void SetFullScreen(bool fullScreen);
	void SetActiveState(std::string key)
	{
		mStateMachine->SetActive(key);
	}
	EventSystem& GetEventSystem()
	{
		return mEventSystem;
	}
	
	virtual ~Game(void);
protected:
	virtual void Render() = 0;
	virtual void Update(double dTime)
	{
		mStateMachine->Update(dTime);
		mKeyboard->Update(dTime);
		mMouse->Update(dTime);
	}
	void Present(UINT syncInterval = 0,UINT flags = 0)
	{
		mSwapChain->Present(syncInterval,flags);
	}
	virtual void OnResize(WPARAM wParam,LPARAM lParam);
	void AddState(std::string key,GameState* state)
	{
		mStateMachine->Add(key,state);
	}
	void RemoveState(std::string key)
	{
		mStateMachine->Erase(key);
	}
private:
	void InitWindow();
	void InitSwapChain();
	void InitDirectX();
	void InitRenderTargetView();
	void InitDepthStencilView();
	void SetViewPort();
	void OpenWindow();
	GameTimer mGameTimer;
	StateMachine* mStateMachine;
	HWND mhWnd;
	HINSTANCE mhInstance;
	int mWidth,mHeight;
	int mShowCmd;
	bool mPaused;
	bool mFullScreen;
	std::wstring mName;
	UINT mRefreshRate;
	double mFrameTime;
	InputSystem mInputSystem;
	OSGFKeyboard* mKeyboard;
	OSGFMouse* mMouse;
	EventSystem mEventSystem;
	//DirectX variables
	ID3D10Device* mDevice;
	IDXGISwapChain* mSwapChain;
	ID3D10RenderTargetView* mRenderTargetView;
	ID3D10Texture2D* mDepthStencilBuffer;
	ID3D10DepthStencilView* mDepthStencilView;
};
LRESULT CALLBACK WindowProc(HWND hWnd,UINT message,WPARAM wParam,
	LPARAM lParam);
