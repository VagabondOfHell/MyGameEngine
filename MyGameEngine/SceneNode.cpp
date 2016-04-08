#include "SceneNode.h"
#include "SimpleModel.h"
#include "Entity.h"

SceneNode::SceneNode(SceneNode* _parent)
{
	parent = _parent;

	position = amVec3();
	scale = amVec3(1.0f, 1.0f, 1.0f);
	orientation = amQuaternion();
}


SceneNode::~SceneNode(void)
{
	//Loop through and destroy all children
	if(children.size() > 0)
	{
		for (int i = 0; i < children.size(); i++)
		{
			if(children[i])
			{
				delete children[i];
				children[i] = NULL;
			}
		}
	}
}

void SceneNode::Render(amMatrix4x4& worldMatrix, amMatrix4x4& projectionMatrix)
{
	for (int i = 0; i < entities.size(); i++)
	{
		if(InFrustum(worldMatrix, projectionMatrix, entities[i]))
		{
			entities[i]->UseShaderProgram();
			entities[i]->SetShaderParameters(worldMatrix, projectionMatrix, GetTransformationMatrix());
			entities[i]->Render();
			printf("DRAWN\n");
		}
		else
			printf("NOT DRAWN\n");
	}

	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Render(worldMatrix, projectionMatrix);
	}
}

bool SceneNode::InFrustum(amMatrix4x4& worldMatrix, amMatrix4x4& projectionMatrix, Entity* entity)
{
	ProjectionFrustum frustumPlanes;

	frustumPlanes = amMatrixMath::ExtractPlanesFromPerspective(projectionMatrix, true);

	BoundingSphere boundSphere = entity->GetBoundingSphere();

	boundSphere.position = worldMatrix * GetTransformationMatrix() * boundSphere.position;

	if(frustumPlanes.bottomPlane.IsBehind(boundSphere))
		return false;

	if(frustumPlanes.topPlane.IsBehind(boundSphere))
		return false;

	if(frustumPlanes.leftPlane.IsBehind(boundSphere))
		return false;

	if(frustumPlanes.rightPlane.IsBehind(boundSphere))
		return false;

	return true;
}
