#include <iostream>
#include <cstring>
#include <set>
#include "OSGFObjMeshLoader.h"
#include "Game.h"
#include "Util.h"
using namespace std;
void OSGFObjMeshLoader::LoadFile(const std::string& fileName)
{
	OSGFTextFileLoader::LoadFile(fileName);
	ParseFile();
	ParseFaces();
	CreateMesh();
	MapMaterials();
	Clean();
}
void OSGFObjMeshLoader::MapMaterials()
{
	if(mMaterials.Size()>0)
	{
		for(map<string,UINT>::iterator itr = mSubsets.begin();
			itr!=mSubsets.end();++itr)
		{
				mUsedMaterials.Put(mMaterials[itr->first]);	
		}
	}
}
void OSGFObjMeshLoader::ParseFile()
{
	string str = GetFile();
	in.open(str);
	if(!in.is_open())throw exception(("File "+str+ "not found").c_str());
	int i = 0;
	while(in)
	{
		char buf[1024];
		in.getline(buf,1024,'\n');
		char* tmp;
		tmp = strtok(buf," ");
		vector<char*> subStrs;
		while(tmp!=0)
		{
			if(tmp[0]=='#')break;
			subStrs.push_back(tmp);
			tmp = strtok(NULL," ");
		}
		if(!subStrs.empty())
		{
			ExecLoader(subStrs[0],subStrs,*this);
		}
	}
	in.close();
}
void OSGFObjMeshLoader::ParseFaces()
{
	for(vector<string>::iterator itr = mFaces.begin(); 
		itr!= mFaces.end();
		++itr)
	{
		ParseFaceElement(itr->c_str());
	}
}
void OSGFObjMeshLoader::CreateMesh()
{
	D3D10_INPUT_ELEMENT_DESC desc[]=
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D10_INPUT_PER_VERTEX_DATA,0},
		{"TEXTURE",0,DXGI_FORMAT_R32G32B32_FLOAT,0,16,D3D10_INPUT_PER_VERTEX_DATA,0},
		{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,28,D3D10_INPUT_PER_VERTEX_DATA,0}

	};
	UINT options = 0;
	options|=D3DX10_MESH_32_BIT;
	vector<DWORD> indices = GetIndices();
	HR(D3DX10CreateMesh(mGame.GetDevice(),desc,3,desc[0].SemanticName,
		mVerts.size(),indices.size()/3,options,&mMesh));
	HR(mMesh->SetIndexData(indices.data(),indices.size()));
	HR(mMesh->SetVertexData(0,mVerts.data()));
	HR(mMesh->SetAttributeData(mAttributeData.data()));
	HR(mMesh->GenerateAdjacencyAndPointReps(0.001));
	HR(mMesh->Optimize(D3DX10_MESHOPT_ATTR_SORT|D3DX10_MESHOPT_VERTEX_CACHE,0,0));
	HR(mMesh->CommitToDevice());
}

void OSGFObjMeshLoader::ParseFaceElement(const string& str)
{
	vector<DWORD> parsedData = vector<DWORD>(3);
	const string key = str;
	char *c = const_cast<char*>(str.c_str());
	strcpy(c,str.c_str());
	if(strstr(c,"/"))
	{
		if(strstr(c,"//"))
		{
			parsedData[0] = atoi(strtok(c,"/"))-1;
			parsedData[2] = atoi(strtok(NULL,"/"))-1;
		}
		else
		{
			parsedData[0] = atoi(strtok(c,"/"))-1;
			parsedData[1] = atoi(strtok(NULL,"/"))-1;
			parsedData[2] = atoi(strtok(NULL,"/"))-1;
		}
	}
	else
	{
		parsedData[0] = atoi(c)-1;
	}
	VertMapIterator itr = mVertMap.find(key);
	if(itr==mVertMap.end())
	{
		mVerts.push_back(CreateVertex(parsedData[0],parsedData[1],parsedData[2]));
		DWORD elemNumber = mVerts.size()-1;
		mVertMap.insert(VertMapPair(key,elemNumber));
		mIndices.push_back(elemNumber);
	}
	else
	{
		mIndices.push_back(itr->second);
	}
}
OSGFObjMeshLoader::Vertex OSGFObjMeshLoader::CreateVertex(int p,int t,int n)
{
	Vertex v;
	v.v = mPositions[p];
	if(mTexture.size()>0)
		v.vt = mTexture[t];
	if(mNormals.size()>0)
		v.vn = mNormals[n];
	return v;
}
void OSGFObjMeshLoader::LoadV::Execute(std::vector<char*>& v,
	OSGFTextFileLoader& l)
{
	while(v.size()<5)
		v.push_back("1.000000");
	D3DXVECTOR4 vert;
	vert.x = (float)atof(v[1]);
	vert.y = (float)atof(v[2]);
	vert.z = (float)atof(v[3]);
	vert.w = (float)atof(v[4]);
	OSGFObjMeshLoader& ol =reinterpret_cast<OSGFObjMeshLoader&>(l);
	ol.mPositions.push_back(vert);
}
void OSGFObjMeshLoader::LoadF::Execute(std::vector<char*> &v,
	OSGFTextFileLoader& l)
{
	int i = v.size();
	OSGFObjMeshLoader& ol =reinterpret_cast<OSGFObjMeshLoader&>(l);
	while(i>3)
	{
		ol.mFaces.push_back(v[1]);
		ol.mFaces.push_back(v[i-2]);
		ol.mFaces.push_back(v[i-1]);
		i--;
		ol.mAttributeData.push_back(ol.mCurrentSubSet);
	}
}
void OSGFObjMeshLoader::LoadVN::Execute(std::vector<char*> &vn,
	OSGFTextFileLoader& l)
{
	while(vn.size()<4)
		vn.push_back("0.0");
	D3DXVECTOR3 norm;
	norm.x = (float)atof(vn[1]);
	norm.y = (float)atof(vn[2]);
	norm.z = (float)atof(vn[3]);
	OSGFObjMeshLoader& ol =reinterpret_cast<OSGFObjMeshLoader&>(l);
	ol.mNormals.push_back(norm);
}
void OSGFObjMeshLoader::LoadVT::Execute(std::vector<char*> &vt,
	OSGFTextFileLoader& l)
{
	while(vt.size()<4)
		vt.push_back("0.0");
	D3DXVECTOR3 text;
	text.x = (float)atof(vt[1]);
	text.y = (float)atof(vt[2]);
	text.z = (float)atof(vt[3]);
	OSGFObjMeshLoader& ol =reinterpret_cast<OSGFObjMeshLoader&>(l);
	ol.mTexture.push_back(text);
}
void OSGFObjMeshLoader::LoadMtlLib::Execute(std::vector<char*> &vn,
	OSGFTextFileLoader& l)
{
	OSGFObjMeshLoader& ml = reinterpret_cast<OSGFObjMeshLoader&>(l);
	OSGFMtlLoader loader(l.GetGame(),l.GetPathToFile()+vn[1]);
	ml.mMaterials = loader.GetMaterials();
}
void OSGFObjMeshLoader::LoadUseMtl::Execute(std::vector<char*> &vn,
	OSGFTextFileLoader& l)
{
	OSGFObjMeshLoader& ml = reinterpret_cast<OSGFObjMeshLoader&>(l);
	map<string,UINT>& subsets = ml.mSubsets;
	if(subsets.find(vn[1])!=subsets.end())
		ml.mCurrentSubSet = subsets[vn[1]];
	else
	{
		ml.mCurrentSubSet = subsets.size();
		subsets[vn[1]]=ml.mCurrentSubSet;
	}

}
void OSGFObjMeshLoader::Clean()
{
	mPositions.clear();
	mNormals.clear();
	mTexture.clear();
	mVerts.clear();
	mIndices.clear();
	mVertMap.clear();
	ClearLoaders();
	mFaces.clear();
}
vector<DWORD> OSGFObjMeshLoader::GetIndices()
{
	return mIndices;
}