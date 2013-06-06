#pragma once
#include <string>
#include "osgf3dmodel.h"
class OSGFCube :
	public OSGF3DModel
{
public:
	OSGFCube(Game& game,std::string effect,std::string technique)
		:OSGF3DModel(game,effect,technique)
	{

	}
	OSGFCube(const OSGFCube& cube)
		:OSGF3DModel(cube)
	{
	}
	virtual OSGFCube* Clone()const
	{
		return new OSGFCube(*this);
	}
	virtual void Initialize();
	virtual void Update(double deltaTime)
	{
		OSGF3DModel::Update(deltaTime);
	}
	virtual void Render()const
	{
		OSGF3DModel::Render();

	}
	virtual ~OSGFCube(void)
	{
	}
private:
	void InitVertices();
	void InitIndices();
	struct Vertex
	{
		D3DXVECTOR3 pos;
		D3DXCOLOR col;
	};
};

