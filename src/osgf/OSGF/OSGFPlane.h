#pragma once
#include "OSGF3DModel.h"
class OSGFPlane
	:public OSGF3DModel
{
public:
	OSGFPlane(Game& game,std::string effect,std::string technique)
		:OSGF3DModel(game,effect,technique)
	{

	}
	virtual void Update(double dTime)
	{
		OSGF3DModel::Update(dTime);
	}
	virtual void Render()const
	{
		OSGF3DModel::Render();
	}
	virtual void Initialize();
	/*{
		OSGF3DModel::Initialize();
		Vertex verts[] =
		{ 
			D3DXVECTOR3(FLT_MAX,1,FLT_MAX),D3DXVECTOR3(1,1,0),D3DXVECTOR3(0,1,0),//UR
			D3DXVECTOR3(FLT_MAX,1,FLT_MIN),D3DXVECTOR3(1,0,0),D3DXVECTOR3(0,1,0),//DR
			D3DXVECTOR3(FLT_MIN,1,FLT_MIN),D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,1,0),//DL
			D3DXVECTOR3(FLT_MIN,1,FLT_MAX),D3DXVECTOR3(0,1,0),D3DXVECTOR3(0,1,0) //Ul
		};
		CreateVertexBuffer(verts,sizeof(verts),sizeof(Vertex));
		DWORD indices[]=
		{
			0, 2, 1,
			0, 3, 2
		};
		CreateIndexBuffer(indices,sizeof(indices));
		D3D10_INPUT_ELEMENT_DESC vertexDesc[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
			{"TEXTURE",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0},
			{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0}
		};
		mEffect->SetTechique(mTechName);
		mEffect->CreateInputLayout(vertexDesc,2);
	}*/
private:
	void InitVertices();
	void InitIndices();
	struct Vertex
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 text;
		D3DXVECTOR3 norm;
	};
};