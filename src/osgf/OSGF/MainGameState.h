#pragma once
#include "OSGFLevel.h"
#include "OSGFScreenText.h"
#include "OSGFCube.h"
#include "OSGFMesh.h"
#include "OSGFSkyBox.h"
class MainGameState :
	public OSGFLevel
{
public:
	MainGameState(Game& game);
	virtual MainGameState* Clone()const
	{
		return new MainGameState(*this);
	}
	virtual void Load();
	virtual void Unload();
	virtual ~MainGameState(void);
	virtual void Render()const;
	virtual void Update(double dTime);
	virtual void HandleInput(double dTime);
	virtual void Initialize();
private:
	void InitializeGraphics();
	void IntializeLight();
	void InitializeCamera();
	OSGFScreenText* screenText1;
	OSGFScreenText* screenText2;
	OSGFDrawableComponentManager* textManager;
	OSGFMesh* mMesh;
	OSGFMesh* cube;
	OSGFSkyBox* mSkyBox;
};

