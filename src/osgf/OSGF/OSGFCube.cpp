#include <D3D10.h>
#include <D3DX10.h>
#include "OSGFCube.h"
#include "Util.h"
void OSGFCube::Initialize()
{
	if(IsInitialized())return;
	OSGF3DModel::Initialize();
	InitVertices();
	InitIndices();
	D3D10_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0}
	};
	CreateInputLayout(vertexDesc,2);
}
void OSGFCube::InitVertices()
{
	Vertex vertices[] =
	{
		{D3DXVECTOR3(-1.0f, -1.0f, -1.0f), OSGFCOLOR_WHITE},
		{D3DXVECTOR3(-1.0f, +1.0f, -1.0f), OSGFCOLOR_WHITE},
		{D3DXVECTOR3(+1.0f, +1.0f, -1.0f), OSGFCOLOR_WHITE},
		{D3DXVECTOR3(+1.0f, -1.0f, -1.0f), OSGFCOLOR_GREEN},
		{D3DXVECTOR3(-1.0f, -1.0f, +1.0f), OSGFCOLOR_BLUE},
		{D3DXVECTOR3(-1.0f, +1.0f, +1.0f), OSGFCOLOR_WHITE},
		{D3DXVECTOR3(+1.0f, +1.0f, +1.0f), OSGFCOLOR_CYAN},
		{D3DXVECTOR3(+1.0f, -1.0f, +1.0f), OSGFCOLOR_WHITE},
	};
	CreateVertexBuffer(vertices,sizeof(vertices),sizeof(Vertex));
}
void OSGFCube::InitIndices()
{
	DWORD indices[] = {
		// front face
		0, 1, 2,
		0, 2, 3,
		// back face
		4, 6, 5,
		4, 7, 6,
		// left face
		4, 5, 1,
		4, 1, 0,
		// right face
		3, 2, 6,
		3, 6, 7,
		// top face
		1, 5, 6,
		1, 6, 2,
		// bottom face
		4, 0, 3, 
		4, 3, 7
	};
	CreateIndexBuffer(indices,sizeof(indices));
}
