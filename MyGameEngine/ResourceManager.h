#pragma once
#include <map>

typedef std::string ResourceHandle;

class ResourceManager
{
public:
	
	ResourceManager(void){}
	virtual ~ResourceManager(void){}

	virtual ResourceHandle LoadResource(std::string filename) = 0;
	virtual void ReleaseResource(ResourceHandle handle) = 0;


};

