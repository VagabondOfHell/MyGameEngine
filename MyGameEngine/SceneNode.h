#pragma once
#include "amQuaternion.h"
#include "amVec3.h"
#include "amMatrixMath.h"
#include "SimpleModel.h"
#include <vector>
#include <vmath.h>

class SceneNode
{
private:
	std::vector<SceneNode*> children;
	std::vector<SimpleModel*> entities;

	SceneNode* parent;

public:
	amVec3 position;
	amVec3 scale;
	amQuaternion orientation;
	
	SceneNode(SceneNode* _parent);
	virtual ~SceneNode(void);

	///<summary>Creates a new node as a child of this one</summary>
	///<returns>The newly created node</returns>
	inline SceneNode* CreateChildSceneNode()
	{
		//Create a new node, setting this node as the parent
		SceneNode* newNode = new SceneNode(this);

		//Add it to the list
		children.push_back(newNode);

		//Return the new node
		return newNode;
	}

	///<summary>Get the scene node that acts as Parent to this node</summary>
	///<returns>A constant pointer to the parent node, or NULL if there is no parent, in which case its the root node</returns>
	inline const SceneNode* const GetParentSceneNode()
	{
		return parent;
	}

	///<summary>Gets the 4x4 Transformation Matrix of the node</summary>
	///<returns>4x4 Matrix representing complete transformation</returns>
	inline amMatrix4x4 GetTransformationMatrix()
	{
		if(parent != NULL)
			return parent->GetTransformationMatrix() * (amMatrix4x4::LoadIdentity() * amMatrixMath::Translate(position.x, position.y, position.z) * 
			amMatrixMath::Rotate(orientation.w, orientation.x, orientation.y, orientation.z) * amMatrixMath::Scale(scale.x, scale.y, scale.z)); 
		else
			return (amMatrix4x4::LoadIdentity() * amMatrixMath::Translate(position.x, position.y, position.z) * 
				amMatrixMath::Rotate(orientation.w, orientation.x, orientation.y, orientation.z) * amMatrixMath::Scale(scale.x, scale.y, scale.z)); 
	}

	///<summary>Attaches an entity to this scene node. Does not check for duplication</summary>
	///<param "model">The model to attach</param>
	inline void AttachModel(SimpleModel* entity)
	{
		entities.push_back(entity);
	}

	void Render(amMatrix4x4& worldMatrix, amMatrix4x4& projectionMatrix);

	bool InFrustum(amMatrix4x4& worldMatrix, amMatrix4x4& projectionMatrix, Entity* entity);
};

