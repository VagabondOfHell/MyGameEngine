#pragma once
#include "resourcemanager.h"
#include "Mesh.h"

class ModelManager :
	public ResourceManager
{
private:
	std::map<std::string, Mesh*> models;

public:
	ModelManager(void);
	~ModelManager(void);

	virtual ResourceHandle LoadResource(std::string filename);
	virtual void ReleaseResource(ResourceHandle handle);

	ResourceHandle LoadCubeModel();

	Mesh* GetMesh(ResourceHandle handle)
	{
		auto iter = models.find(handle);

		if(iter != models.end())
			return iter->second;

		return NULL;
	}
};

