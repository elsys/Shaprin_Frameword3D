#pragma once
#include "OSGF3DModel.h"
class OSGFSkyBox
	:public OSGF3DModel
{
public:
	OSGFSkyBox(Game& game,const std::string& effect,const std::string& tech)
		:OSGF3DModel(game,effect,tech)
	{

	}
	virtual void Update(double dTime)
	{
		OSGF3DModel::Update(dTime);
		SetTranslation(GetCamera()->GetPosition());
	}
	virtual void Initialize();
private:
	void InitVertices();
	void InitIndices();
	struct Vertex
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR2 texture;
	};
};