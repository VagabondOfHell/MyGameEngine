#pragma once
#include "GameEngine.h"
#include "SimpleModel.h"

class DemoApp : public GameEngine
{
public:
	SimpleModel* model;
	SceneNode* modelNode;
	SceneNode* modelNodeChild;
	SceneNode* modelNodeChild2;

	DemoApp(void);
	virtual ~DemoApp(void);

	virtual void OnStart();
	virtual void PreRender(float time);
	virtual void Render();
	virtual void PostRender();
	virtual void OnEnd();
};

