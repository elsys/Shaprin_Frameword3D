#pragma once
#include <map>
#include <string>
#include <vector>
#include <D3DX10.h>
#include "Game.h"
#include "MaterialContainer.h"
#include "OSGFTextFileLoader.h"
class OSGFMtlLoader
	: public OSGFTextFileLoader
{
	typedef std::pair<std::string,Loader> p;
public:	
	OSGFMtlLoader(Game& game)
		:OSGFTextFileLoader(game){}
	OSGFMtlLoader(Game& game, const std::string& fileName);
	OSGFMtlLoader(const OSGFMtlLoader& m)
		:OSGFTextFileLoader(m),mFileName(m.mFileName),mMtrls(m.mMtrls)
	{
		
	}
	virtual OSGFMtlLoader* Clone()
	{
		return new OSGFMtlLoader(*this);
	}
	virtual void LoadFile(const std::string& fileName);
	const MaterialContainer& GetMaterials()
	{
		return mMtrls;
	}
	void Clear()
	{
		ClearLoaders();
	}
	~OSGFMtlLoader()
	{
		Clear();
	}
protected:
	virtual void InitLoaders();
private:
	class ProcessNewMtl
		:public Loader
	{
		virtual void Execute(std::vector<char*>& toks,OSGFTextFileLoader& l);
	};
	class ProcessKa
		:public Loader
	{
		virtual void Execute(std::vector<char*>& toks,OSGFTextFileLoader& l)
		{
			OSGFMtlLoader& ml = reinterpret_cast<OSGFMtlLoader&>(l);
			ml.mMtrl.ambient = ParseVector(toks);
		}
	};
	class ProcessKd
		:public Loader
	{
		virtual void Execute(std::vector<char*>& toks,OSGFTextFileLoader& l)
		{
			OSGFMtlLoader& ml = reinterpret_cast<OSGFMtlLoader&>(l);
			ml.mMtrl.diffuse = ParseVector(toks);
		}
	};
	class ProcessKs
		:public Loader
	{
		virtual void Execute(std::vector<char*>& toks,OSGFTextFileLoader& l)
		{
			OSGFMtlLoader& ml = reinterpret_cast<OSGFMtlLoader&>(l);
			ml.mMtrl.specular = ParseVector(toks);
		}
	};
	class ProcessMapKd
		:public Loader
	{
		virtual void Execute(std::vector<char*>& toks,OSGFTextFileLoader& l)
		{
			OSGFMtlLoader& ml = reinterpret_cast<OSGFMtlLoader&>(l);
			std::string file =ml.GetPathToFile() + toks[1];
			HR(D3DX10CreateShaderResourceViewFromFileA(ml.mGame.GetDevice(),
				file.c_str(),NULL,NULL,&ml.mMtrl.texture,NULL));
		}
	};
	static D3DXVECTOR3 ParseVector(
		const std::vector<char*>& toks)
	{
		return D3DXVECTOR3(atof(toks[1]),
			atof(toks[2]),atof(toks[3]));
	}
	std::string mFileName;
	MaterialContainer mMtrls;
	Material mMtrl;
};