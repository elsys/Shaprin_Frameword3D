#include <Windows.h>
#include <fstream>
#include "Game.h"
#include "Util.h"
using namespace std;
Game::Game(HINSTANCE hInstance,int nShowCmd,wstring aName,
int aWidth,int aHeight,int aRefreshRate)
	:mhInstance(hInstance),mWidth(aWidth),mHeight(aHeight),mShowCmd(nShowCmd),
	 mPaused(false),mName(aName),mRefreshRate(aRefreshRate),mFrameTime(1.0/mRefreshRate),
	 mRenderTargetView(NULL),mDevice(NULL),mSwapChain(NULL),mDepthStencilBuffer(NULL),
	 mDepthStencilView(NULL),mFullScreen(false)
{
}
void Game::Initialize()
{
	InitWindow();
	InitDirectX();
	mStateMachine = new StateMachine(*this);
	mKeyboard = new OSGFKeyboard(*this);
	mMouse = new OSGFMouse(*this);
	mInputSystem.SetKeyboard(mKeyboard);
	mInputSystem.SetMouse(mMouse);
}
void Game::Run()
{
	OpenWindow();
}
void Game::SetScreenSize(int width,int height)
{
	if(mhWnd)
	{	
		SetWindowPos(mhWnd,NULL,0,0,width,height,SWP_NOMOVE|SWP_NOZORDER);
	}
	else
	{
		mWidth = width;
		mHeight = height;
	}
}

void Game::SetFullScreen(bool aFullScreen)
{
	mFullScreen = aFullScreen;
	if(mSwapChain)
		mSwapChain->SetFullscreenState(aFullScreen,NULL);
}
void Game::InitWindow()
{
	WNDCLASSEX wc;
	ZeroMemory(&wc,sizeof(wc));
	wc.style =  wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = mhInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = mName.c_str();
	RegisterClassEx(&wc);
	mhWnd = CreateWindowEx(NULL,
						  mName.c_str(),
						  mName.c_str(),
						  WS_OVERLAPPEDWINDOW,
						  200,
						  200,
						  mWidth,
						  mHeight,
						  NULL,
						  NULL,
						  mhInstance,
						  this);
}
void Game::InitDirectX()
{
	InitSwapChain();
	SetScreenSize(mWidth,mHeight);
}
void Game::InitSwapChain()
{
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferCount = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.Height = mHeight;
	sd.BufferDesc.Width = mWidth;
	sd.BufferDesc.RefreshRate.Numerator = mRefreshRate;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Flags = 0;
	sd.OutputWindow = mhWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed = !mFullScreen;
	UINT createDeviceFlags = 0;
#if defined(DEBUG)||defined(_DEBUG)
	createDeviceFlags |=D3D10_CREATE_DEVICE_DEBUG;
#endif
	HR(D3D10CreateDeviceAndSwapChain(NULL,D3D10_DRIVER_TYPE_HARDWARE,0,
								  createDeviceFlags,D3D10_SDK_VERSION,&sd,
								  &mSwapChain,&mDevice));
}
void Game::InitRenderTargetView()
{
	ID3D10Texture2D* backBuffer;
	HR(mSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(mDevice->CreateRenderTargetView(backBuffer, 0, &mRenderTargetView));
	ReleaseCom(backBuffer);
}
void Game::InitDepthStencilView()
{
	D3D10_TEXTURE2D_DESC dsdesc;
	dsdesc.ArraySize = 1;
	dsdesc.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	dsdesc.CPUAccessFlags = 0;
	dsdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsdesc.Height = mHeight;
	dsdesc.Width = mWidth;
	dsdesc.MipLevels  = 1;
	dsdesc.MiscFlags = 0;
	dsdesc.SampleDesc.Count = 1;
	dsdesc.SampleDesc.Quality = 0;
	dsdesc.Usage = D3D10_USAGE_DEFAULT;
	HR(mDevice->CreateTexture2D(&dsdesc,NULL,&mDepthStencilBuffer));
	HR(mDevice->CreateDepthStencilView(mDepthStencilBuffer,NULL,&mDepthStencilView));
}
void Game::SetViewPort()
{
	D3D10_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = mWidth;
	vp.Height = mHeight;
	vp.MaxDepth = 1.0f;
	vp.MinDepth = 0.0f;
	mDevice->RSSetViewports(1,&vp);
}
void Game::OpenWindow()
{
	ShowWindow(mhWnd,mShowCmd);
	MSG msg;
	mGameTimer.Reset();
	double baseTime = 0;
	while(true)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if(msg.message == WM_QUIT)
				break;
		}
		mGameTimer.Tick();	
		if(!mPaused)
		{
			double dTime=mGameTimer.GetGameTime()-baseTime;
			Update(dTime);
			if(dTime>=mFrameTime)
			{
				Render();
				baseTime+=dTime;
			}
		}
	}
}
void Game::ClearColorDephtStencil(D3DXCOLOR color,
	FLOAT depth,UINT8 stencil)const
{
	mDevice->ClearRenderTargetView(mRenderTargetView,(FLOAT*)color);
	mDevice->ClearDepthStencilView(mDepthStencilView,
		D3D10_CLEAR_DEPTH|D3D10_CLEAR_STENCIL,depth,stencil);
}
Game::~Game(void)
{
	ReleaseCom(mDevice);
	ReleaseCom(mSwapChain);
	ReleaseCom(mRenderTargetView);
	ReleaseCom(mDepthStencilBuffer);
	ReleaseCom(mDepthStencilView);
	SafeDelete(mStateMachine);
	SafeDelete(mKeyboard);
	SafeDelete(mMouse);
}
void Game::Pause()
{
	if(!mPaused)
	{
		mPaused = true;
		mGameTimer.Stop();
	}
}
void Game::Unpause()
{
	if(mPaused)
	{
		mPaused = false;
		mGameTimer.Start();
	}
}
void Game::OnResize(WPARAM wParam,LPARAM lParam)
{
 	mWidth = max(LOWORD(lParam),1);
	mHeight = max(HIWORD(lParam),1);
	ReleaseCom(mRenderTargetView);
	ReleaseCom(mDepthStencilView);
	ReleaseCom(mDepthStencilBuffer);
	mStateMachine->OnScreenResize(lParam,lParam);
	HR(mSwapChain->ResizeBuffers(1, mWidth, mHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	InitRenderTargetView();
	InitDepthStencilView();
	mDevice->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
	SetViewPort();
}

LRESULT CALLBACK Game::MsgProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_ACTIVATE:
			if(LOWORD(wParam)==WA_INACTIVE)
				Pause();
			else
				Unpause();
		break;
		case WM_INPUT:
			mInputSystem.HandleInput(wParam,lParam);
		break;
		case WM_SIZE:
			OnResize(wParam,lParam);
		break;
		default:
			return DefWindowProc(mhWnd,msg,wParam,lParam);
	}
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, 
	WPARAM wParam, LPARAM lParam)
{
	static Game* app = 0;

	switch( msg )
	{
		case WM_CREATE:
		{
			
			CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
			app = (Game*)cs->lpCreateParams;
			return 0;
		}
		case WM_DESTROY:
			PostMessage(hWnd,WM_QUIT,0,0);
		break;
	}
	if( app )
		return app->MsgProc(msg, wParam, lParam);
	else
		return DefWindowProc(hWnd, msg, wParam, lParam);
}