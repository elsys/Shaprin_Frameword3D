#pragma once
#include "OSGFComponent.h"
class OSGFStringMeshLoader
	:OSGFComponent
{
	typedef void (OSGFObjMeshLoader::*Loader)(std::vector<char*>&);
	typedef std::pair<std::string,Loader> p;
	typedef std::map<std::string,DWORD> VertMap;
	typedef std::pair<std::string,DWORD> VertMapPair;
	typedef VertMap::iterator VertMapIterator;
};