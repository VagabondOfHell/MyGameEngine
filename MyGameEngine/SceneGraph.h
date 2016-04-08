#pragma once
#include "SceneNode.h"
#include "Camera.h"

class SceneManager;

class SceneGraph
{
private:
	SceneNode* rootNode;
	SceneManager* sceneManager;

public:
	SceneGraph(void);
	~SceneGraph(void);

	inline SceneNode& GetRootSceneNode()
	{
		return *rootNode;
	}

	inline SceneNode* CreateRootChildSceneNode()
	{
		return rootNode->CreateChildSceneNode();
	}

	void RenderScene(amMatrix4x4& worldMatrix, amMatrix4x4& projectionMatrix);
};

