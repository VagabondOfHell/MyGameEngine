#include "SceneGraph.h"


SceneGraph::SceneGraph(void)
{
	rootNode = new SceneNode(NULL);
}

SceneGraph::~SceneGraph(void)
{
	if(rootNode)
	{
		delete rootNode;
		rootNode = NULL;
	}
}

void SceneGraph::RenderScene(amMatrix4x4& worldMatrix, amMatrix4x4& projectionMatrix)
{
	rootNode->Render(worldMatrix, projectionMatrix);
}
