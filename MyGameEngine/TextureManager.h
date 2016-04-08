#pragma once
#include "resourcemanager.h"
class TextureManager :
	public ResourceManager
{
private:

public:
	TextureManager(void);
	virtual ~TextureManager(void);

	virtual ResourceHandle LoadResource(std::string filename);
	virtual void ReleaseResource(ResourceHandle handle);
};

