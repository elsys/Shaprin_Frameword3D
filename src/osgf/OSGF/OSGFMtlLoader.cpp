#include <exception>
#include <fstream>
#include "OSGFMtlLoader.h"
using namespace std;
OSGFMtlLoader::OSGFMtlLoader(Game& game, const std::string& fileName)
	:OSGFTextFileLoader(game,fileName)
{
	LoadFile(fileName);
}
void OSGFMtlLoader::LoadFile(const string& fileName)
{
	OSGFTextFileLoader::LoadFile(fileName);
	InitLoaders();
	mFileName = fileName;
	ifstream in(mFileName);
	if(!in.is_open())
		throw exception(("File: "+fileName+" not found").c_str());
	char buf[512];
	while(in)
	{
		in.getline(buf,512);
		char* tmp = strtok(buf," ");
		vector<char*> subStrs;
		while(tmp!=0)
		{
			if(tmp[0]=='#')break;
			subStrs.push_back(tmp);
			tmp = strtok(NULL," ");
		}
		if(subStrs.size()>0)
			ExecLoader(subStrs[0],subStrs,*this);
	}
	if(mMtrl.MaterialName!="")
		mMtrls.Put(mMtrl);
	if(!in.eof())
		throw exception(("Error in reading file: "+mFileName).c_str());

}
void OSGFMtlLoader::ProcessNewMtl::Execute(vector<char*>& toks,OSGFTextFileLoader& l)
{
	OSGFMtlLoader& ml = reinterpret_cast<OSGFMtlLoader&>(l);
	if(ml.mMtrl.MaterialName!="")
	{
		ml.mMtrls.Put(ml.mMtrl);
	}
	ml.mMtrl = Material();
	ml.mMtrl.MaterialName = toks[1];
}
void OSGFMtlLoader::InitLoaders()
{
	PutLoader("newmtl",new ProcessNewMtl());
	PutLoader("Ka",new ProcessKa());
	PutLoader("Ks",new ProcessKs());
	PutLoader("Kd",new ProcessKd());
	PutLoader("map_Kd",new ProcessMapKd());
}
