#include "OSGFPlane.h"
void OSGFPlane::Initialize()
{
	if(IsInitialized())return;
	OSGF3DModel::Initialize();
	InitVertices();
	InitIndices();
	D3D10_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"TEXTURE",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0}
	};
	mEffect->SetTechique(mTechName);
	mEffect->CreateInputLayout(vertexDesc,3);
}
void OSGFPlane::InitVertices()
{
	float x = 34000000.0f;
	Vertex vertices[] =
	{	
		{D3DXVECTOR3(-1.0f*x, 0, -1.0f*x), D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,1,0)},
		{D3DXVECTOR3(-1.0f*x, 0, 1.0f*x), D3DXVECTOR3(0,1,0),D3DXVECTOR3(0,1,0)},
		{D3DXVECTOR3(1.0f*x, 0, 1.0f*x), D3DXVECTOR3(1,1,0),D3DXVECTOR3(0,1,0)},
		{D3DXVECTOR3(1.0f*x, 0, -1.0f*x), D3DXVECTOR3(1,0,0),D3DXVECTOR3(0,1,0)}
	};
	CreateVertexBuffer(vertices,sizeof(vertices),sizeof(Vertex));
}
void OSGFPlane::InitIndices()
{
	DWORD indices[] = {
		0, 1, 2,
		0, 2, 3,
	};
	CreateIndexBuffer(indices,sizeof(indices));
}
