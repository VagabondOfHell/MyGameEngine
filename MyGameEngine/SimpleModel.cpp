#include "SimpleModel.h"
#include "LoadShaders.h"

SimpleModel::SimpleModel(void)
{
}

SimpleModel::~SimpleModel(void)
{
	
}

void SimpleModel::Initialize()
{
	ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "..\\MyGameEngine\\SimpleModel.vert" },
			{ GL_FRAGMENT_SHADER, "..\\MyGameEngine\\SimpleModel.frag" },
			{ GL_NONE, NULL }
	};

	shaderProgram = LoadShaders(shaders);
}

bool SimpleModel::LoadModel(std::string& modelFileName)
{
	return true;
}

void SimpleModel::SetShaderParameters(amMatrix4x4& worldMatrix, amMatrix4x4& projectionMatrix, amMatrix4x4& modelViewMatrix)
{
	modelviewUniform = glGetUniformLocation(shaderProgram, "ModelView");
	worldViewUniform = glGetUniformLocation(shaderProgram, "WorldView");
	projectionUniform = glGetUniformLocation(shaderProgram, "Projection");
	
	glUniformMatrix4fv(worldViewUniform, 1, GL_FALSE, (GLfloat*)&worldMatrix[0]);
	glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, (GLfloat*)&projectionMatrix[0]);

	glUniformMatrix4fv(modelviewUniform, 1, GL_FALSE, (GLfloat*)&modelViewMatrix[0]);
}

BoundingSphere SimpleModel::GetBoundingSphere()
{
	amVec3 center = ((mesh->maxVertex - mesh->minVertex) / 2.0f) + mesh->minVertex;
	return BoundingSphere(center, (center - mesh->minVertex).GetMagnitude()); 
}

void SimpleModel::Render()
{	
	glBindVertexArray(mesh->vao);

	glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[Buffers::Vertex]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vbos[Buffers::Index]);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);

	glBindVertexArray(0);
}