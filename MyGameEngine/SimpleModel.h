#pragma once
#include "vgl.h"
#include <string>
#include "amMatrixMath.h"
#include "vmath.h"
#include "Entity.h"
#include "BoundingSphere.h"
#include "Mesh.h"

class SimpleModel : public Entity
{
private:
	enum Buffers{ Vertex, Index, NumberOfBuffers};

	GLuint shaderProgram;
	
	Mesh* mesh;

	GLuint modelviewUniform;
	GLuint worldViewUniform;
	GLuint projectionUniform;

public:
	SimpleModel(void);
	virtual ~SimpleModel(void);

	void Initialize();

	void ApplyMesh(Mesh* _mesh)
	{
		mesh = _mesh;
	}

	bool LoadModel(std::string& modelFileName);

	BoundingSphere GetBoundingSphere();

	void Render();

	void SetShaderParameters(amMatrix4x4& worldMatrix, amMatrix4x4& projectionMatrix, amMatrix4x4& modelViewMatrix);

	///<summary>Gets the shader program used to draw this model</summary>
	///<returns>The GL Address to the Shader Program</returns>
	inline GLuint GetShaderProgram()
	{
		return shaderProgram;
	}

	inline void UseShaderProgram()
	{
		glUseProgram(shaderProgram);
	}

	///<summary>Gets the specified vertex buffer</summary>
	///<params "buffer">The buffer to get </params>
	///<returns>The GL Address to the requested vertex buffer</returns>
	inline GLuint GetGLBuffer(Buffers buffer)
	{
		return mesh->vbos[buffer];
	}
};

