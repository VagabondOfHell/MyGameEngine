#pragma once
#include "vgl.h"
#include "amVec3.h"

class Mesh
{
public:
	enum Buffers{ Vertex, Index, NumberOfBuffers};

	GLuint vao;
	GLuint vbos[Buffers::NumberOfBuffers];

	amVec3 minVertex, maxVertex;

	~Mesh()
	{
		glDeleteBuffers(Buffers::NumberOfBuffers, vbos);
		glDeleteVertexArrays(1, &vao);
	}
};