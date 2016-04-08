#include "ModelManager.h"

ModelManager::ModelManager(void)
{
}


ModelManager::~ModelManager(void)
{
}

ResourceHandle ModelManager::LoadResource(std::string filename)
{
	auto iter = models.find(filename);

	if(iter != models.end())
	{
		return iter->first;
	}
}
	
ResourceHandle ModelManager::LoadCubeModel()
{
	auto iter = models.find("Cube");

	if(iter != models.end())
	{
		return "Cube";
	}

	GLfloat vertices[24] = {
		-0.5f, 0.5f, 0.5f, //front top left
		0.5f, 0.5f, 0.5f, //front top right
		-0.5f, -0.5f, 0.5f, //front bottom left
		0.5f, -0.5f, 0.5f, //front bottom right
		-0.5f, 0.5f, -0.5f, //back top left
		0.5f, 0.5f, -0.5f, //back top right
		-0.5f, -0.5f, -0.5f, //back bottom left
		0.5f, -0.5f, -0.5f//back bottom right
	};

	GLuint indices[36] = {
		0, 1, 2, //front face
		2, 1, 3,
		3, 2, 6, //Bottom face
		6, 3, 7, 
		7, 3, 1, //Right face
		1, 7, 5, 
		5, 7, 6, //Back face
		6, 5, 4, 
		4, 5, 1, //Top face
		1, 4, 0, 
		0, 2, 6, //Left face
		6, 0, 4
	};

	Mesh* mesh = new Mesh();

	mesh->minVertex = amVec3(-0.5f, -0.5f, -0.5f);
	mesh->maxVertex = -mesh->minVertex;

	//Generate object
	glGenVertexArrays(1, &mesh->vao);
	//Bind object
	glBindVertexArray(mesh->vao);
	//Generate buffers
	glGenBuffers(Mesh::Buffers::NumberOfBuffers, mesh->vbos);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[Mesh::Buffers::Vertex]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vbos[Mesh::Buffers::Index]);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	models.insert(std::pair<std::string, Mesh*>("Cube", mesh));
	return "Cube";
}

void ModelManager::ReleaseResource(ResourceHandle handle)
{
	auto iter = models.find(handle);

	if(iter != models.end())
	{
		delete iter->second;

		models.erase(iter);
	}
}