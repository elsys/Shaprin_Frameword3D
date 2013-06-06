#pragma once

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <D3DX10.h>
#include "OSGFMesh.h"
#include "OSGFTextFileLoader.h"
#include "osgfcomponent.h"
#include "OSGFMtlLoader.h"
class OSGFObjMeshLoader :
	public OSGFTextFileLoader
{
	typedef std::map<std::string,DWORD> VertMap;
	typedef std::pair<std::string,DWORD> VertMapPair;
	typedef VertMap::iterator VertMapIterator;
	struct Vertex
	{
		Vertex()
			:vt(0,0,0),vn(0,0,0),v(0,0,0,0)
		{}
		Vertex(const D3DXVECTOR4& av,D3DXVECTOR3 at, D3DXVECTOR4 an)
			:v(av),vt(at),vn(an)
		{
		}
		D3DXVECTOR4 v;
		D3DXVECTOR3 vt;
		D3DXVECTOR3 vn;

	};
public:
	OSGFObjMeshLoader(Game& game)
		:OSGFTextFileLoader(game)
	{

	}
	OSGFObjMeshLoader(Game& game,std::string file)
		:OSGFTextFileLoader(game,file)
	{
		
	}
	OSGFObjMeshLoader(const OSGFObjMeshLoader& l)
		:OSGFTextFileLoader(l)
	{
		if(l.mMesh)
		{
			mMesh = l.mMesh;
			mMesh->AddRef();
		}
		if(l.mUsedMaterials.Size()>0)
			mUsedMaterials = l.mUsedMaterials;
	}
	OSGFMesh* GetMesh(std::string effect,std::string tech)
	{

		OSGFMesh *m = new OSGFMesh(mGame,mMesh,effect,tech,mUsedMaterials);
		m->Initialize();
		return m;
	}
	virtual void LoadFile(const std::string& fileName);
	virtual ~OSGFObjMeshLoader(void)
	{
		in.close();
	}
protected:
	virtual void InitLoaders()
	{
		PutLoader("v",new LoadV());
		PutLoader("vn",new LoadVN());
		PutLoader("f",new LoadF());
		PutLoader("vt",new LoadVT());
		PutLoader("mtllib",new LoadMtlLib());
		PutLoader("usemtl",new LoadUseMtl());
	}
private:
	void ParseFile();
	class LoadV:public Loader
	{
	public:
		virtual void Execute(std::vector<char*>& v,
			OSGFTextFileLoader& l);
	};
	class LoadF:public Loader
	{
	public:
		virtual void Execute(std::vector<char*> &v,
			OSGFTextFileLoader& l);
	};
	class LoadVN:public Loader
	{
	public:
		virtual void Execute(std::vector<char*> &vn,
			OSGFTextFileLoader& l);
	};
	class LoadVT
		:public Loader
	{
	public:
		virtual void Execute(std::vector<char*> &vn,
			OSGFTextFileLoader& l);
	};
	class LoadMtlLib:public Loader
	{
		virtual void Execute(std::vector<char*> &v,
			OSGFTextFileLoader& l);	
	};
	class LoadUseMtl:public Loader
	{
		virtual void Execute(std::vector<char*> &v,
			OSGFTextFileLoader& l);
	};
	void CreateMesh();
	void Clean();
	void MapMaterials();
	Vertex CreateVertex(int p,int t,int n);
	std::vector<DWORD> GetIndices();
	void ParseFaces();
	void ParseFaceElement(const std::string& str);
	std::ifstream in;
	std::vector<D3DXVECTOR4> mPositions;
	std::vector<D3DXVECTOR3> mNormals;
	std::vector<D3DXVECTOR3> mTexture;
	std::vector<std::string> mFaces;
	MaterialContainer mMaterials;
	MaterialContainer mUsedMaterials;
	std::vector<Vertex> mVerts;
	std::vector<DWORD> mIndices;
	VertMap mVertMap;
	ID3DX10Mesh *mMesh;
	UINT mCurrentSubSet;
	std::map<std::string,UINT> mSubsets;
	std::vector<UINT> mAttributeData;
};
