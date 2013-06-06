#include<exception>
#include<iostream>
#include<Windows.h>
#include"Test.h"
using namespace std;
//#undef DEBUG
//#undef _DEBUG
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
	PSTR cmdLine, int nShowCmd)
{
#if !defined(DEBUG)&!defined(_DEBUG)
	try
#endif
	{
		Test* game = new  Test(hInstance,nShowCmd,L"Test",100,50);
		game->Initialize();
		game->Run();
		delete game;
	}
#if !defined(DEBUG)&!defined(_DEBUG)
	catch(exception e)
	{
		MessageBoxA(NULL,e.what(),"Exception!!!",MB_OK|MB_ICONERROR);
	}
#endif
	return 0;
}
