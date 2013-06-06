#pragma once
#include <string>
#include <vector>
#include <D3DX10.h>
#include "Util.h"
struct Material
{
	Material()
		:ambient(),specular(),diffuse(),texture(NULL),
		MaterialName(""),alpha(1)
	{

	}
	Material(const Material& m)
	{
		Copy(m);
	}
	Material& operator=(const Material& m)
	{
		if(this!=&m)
		{
			ReleaseCom(texture);
			Copy(m);
		}
		return *this;
	}
	D3DXVECTOR3 ambient;
	D3DXVECTOR3 specular;
	D3DXVECTOR3 diffuse;
	ID3D10ShaderResourceView* texture;
	std::string MaterialName;
	float alpha;
	~Material()
	{
		ReleaseCom(texture);
	}
private:
	void Copy(const Material& m)
	{
		texture = m.texture;
		if(texture)
			texture->AddRef();
		ambient = m.ambient;
		diffuse = m.diffuse;
		specular = m.specular;
		alpha = m.alpha;
		MaterialName = m.MaterialName;
	}
};
class MaterialContainer
{
public:
	Material& operator[](unsigned long int i)
	{
		return mMaterials.at(i);
	}
	UINT Size()const 
	{
		return mMaterials.size();
	}
	Material& operator[](std::string name)
	{
		for(UINT i = 0;i<mMaterials.size();++i)
		{
			Material& m = mMaterials[i];
			if(m.MaterialName==name)
				return m; 
		}
		throw std::out_of_range("Material "+name+" not found");;
	}
	const Material& operator[](unsigned long int i)const
	{
		return mMaterials[i];
	}
	void Put(const Material& material)
	{
		mMaterials.push_back(material);
	}
private:
	std::vector<Material> mMaterials;
};