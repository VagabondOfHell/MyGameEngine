#pragma once
#include "Camera.h"
#include "SceneGraph.h"

class SceneManager
{
private:
	SceneGraph* sceneGraph;
	Camera* activeCamera;

public:
	SceneManager(void);
	~SceneManager(void);

	inline void SetActiveCamera(Camera* camera)
	{
		activeCamera = camera;
	}

	inline void RenderScene()
	{
		sceneGraph->RenderScene(activeCamera->GetWorldMatrix(), activeCamera->perspectiveMatrix);
	}

	inline SceneNode& GetRootSceneNode()
	{
		return sceneGraph->GetRootSceneNode();
	}

	inline SceneNode* CreateRootChildSceneNode()
	{
		return sceneGraph->CreateRootChildSceneNode();
	}
};

