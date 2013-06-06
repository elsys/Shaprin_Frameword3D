#pragma once
#include <map>
#include <string>
#include <vector>
#include "OSGFComponent.h"
class OSGFTextFileLoader
	:public OSGFComponent
{
public:
class Loader
{
public:
	virtual void Execute(std::vector<char*>& ch,
		OSGFTextFileLoader& l)=0;
	void operator()(std::vector<char*>& ch
		,OSGFTextFileLoader& l)
	{
		Execute(ch,l);
	}
};
typedef std::map<std::string,Loader*> LoadersMap;
typedef std::pair<std::string,Loader*> p;
public:
	OSGFTextFileLoader(Game& game)
		:OSGFComponent(game),mFileName()
	{
		
	}
	OSGFTextFileLoader(Game& game,std::string fileName)
		:OSGFComponent(game)
	{
		SplitFilename(fileName);
	}
	OSGFTextFileLoader(const OSGFTextFileLoader& l)
		:OSGFComponent(l),mFileName(l.mFileName),mPathToFile(l.mPathToFile),
		mLoaders(l.mLoaders)
	{

	}
	virtual void Initialize()
	{
		if(IsInitialized())return;
		OSGFComponent::Initialize();
		InitLoaders();
		if(mFileName!="")
			LoadFile(mFileName);
	}
	virtual void LoadFile(const std::string& fileName)
	{
		if(mFileName == "")
			SplitFilename(fileName);
	}
	const std::string& GetFileName()const
	{
		return mFileName;
	}
	std::string GetFile()const 
	{
		return mPathToFile+mFileName;
	}
	const std::string& GetPathToFile()const
	{
		return mPathToFile;
	}
protected:
	void PutLoader(const std::string& name,Loader* loader)
	{
		mLoaders.insert(p(name,loader));
	}
	void OnMissingLoader(std::vector<char*> ch)
	{
		char* str = new char[20+strlen(ch[0])];
		sprintf(str,"Unknown command %s\n",ch[0]);
		OutputDebugStringA(str);
		delete str;
	}
	void ExecLoader(const std::string& name,
		std::vector<char*>& ch,OSGFTextFileLoader& l)
	{
		Loader* load = mLoaders[name];
		if(load!=0)
			load->Execute(ch,l);
		else
			OnMissingLoader(ch);
	}
	void ClearLoaders()
	{
		mLoaders.clear();
	}
	virtual void InitLoaders()=0;
private:
	void SplitFilename (const std::string& str)
	{
	  size_t found;
	  found=str.find_last_of("/\\");
	  mPathToFile = str.substr(0,found);
	  mPathToFile+='/';
	  mFileName = str.substr(found+1);
	}
	std::string mFileName;
	std::string mPathToFile;
	LoadersMap mLoaders;
};