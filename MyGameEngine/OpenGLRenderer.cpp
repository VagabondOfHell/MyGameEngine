#include "OpenGLRenderer.h"
#include <cmath>

OpenGLRenderer::OpenGLRenderer(void)
{
	
}


OpenGLRenderer::~OpenGLRenderer(void)
{
	if(Buffers)
		glDeleteBuffers(4, Buffers);

	if(VAOs)
		glDeleteVertexArrays(4, VAOs);
}

bool OpenGLRenderer::Initialize()
{
	glewInit();
	
	ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "..\\MyGameEngine\\MinimalVertexShader.vert" },
			{ GL_FRAGMENT_SHADER, "..\\MyGameEngine\\MinimalFragmentShader.frag" },
			{ GL_NONE, NULL }
	};

	shaderProgram = LoadShaders(shaders);

	if(shaderProgram == 0)
		return false;

	glGenVertexArrays((GLsizei)ShapeArrayObject::NumberOfShapes, VAOs);
	
	///Change 4 to Number of buffers later
	for (int i = 0; i < 4; i++)
	{
		glBindVertexArray(VAOs[i]);

		//Change this to accept Colors later (1 = BufferArrayObject::Number of Buffers,
		//Pass in starting point of each buffer (i.e. i * NumberOfBuffers)
		glGenBuffers(1, &Buffers[i]);
	}
	
	return true;
}

void OpenGLRenderer::RenderPrimitive(PrimitiveType primitive)
{
	switch (primitive)
	{
	case AbstractRenderer::Point:
		RenderPoint();
		break;
	case AbstractRenderer::Line:
		RenderLine();
		break;
	case AbstractRenderer::Triangle:
		RenderTriangle();
		break;
	case AbstractRenderer::Quad:
		RenderQuad();
		break;
	default:
		break;
	}
}

void OpenGLRenderer::RenderPoint()
{
	glUseProgram(shaderProgram);

	GLfloat points[3] = {0.0f, 0.0f, 0.0f};

	glBindVertexArray(VAOs[ShapeArrayObject::Line]);

	glEnableVertexAttribArray(0);
	///Need to modify binding when adding color
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ShapeArrayObject::Line]);

	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), points, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glDrawArrays(GL_POINTS, 0, 1); // Draw our line

	glDisableVertexAttribArray(0);

	glBindVertexArray(0); // Disable our Vertex Buffer Object  
}

void OpenGLRenderer::RenderLine()
{
	glUseProgram(shaderProgram);

	GLfloat points[6] = {-1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f, 0.0f};

	glBindVertexArray(VAOs[ShapeArrayObject::Line]);

	glEnableVertexAttribArray(0);
	///Need to modify binding when adding color
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ShapeArrayObject::Line]);

	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), points, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glDrawArrays(GL_LINES, 0, 2); // Draw our line

	glDisableVertexAttribArray(0);

	glBindVertexArray(0); // Disable our Vertex Buffer Object  
}

void OpenGLRenderer::RenderTriangle()
{
	glUseProgram(shaderProgram);

	GLfloat points[9] = {-1.0f, 0.0f, 0.0f, 
							1.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f}; 

	glBindVertexArray(VAOs[ShapeArrayObject::Triangle]);

	glEnableVertexAttribArray(0);
	///Need to modify binding when adding color
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ShapeArrayObject::Triangle]);

	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), points, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3); // Draw our line

	glDisableVertexAttribArray(0);

	glBindVertexArray(0); // Disable our Vertex Buffer Object  
}

void OpenGLRenderer::RenderQuad()
{
	glUseProgram(shaderProgram);

	GLfloat points[12] = {
							0.5f, 0.5f,	0.0f,  // Top Right
							0.5f, -0.5f, 0.0f,   // Bottom Right
							-0.5f, -0.5f, 0.0f,  // Bottom Left
							-0.5f, 0.5f, 0.0f
	};

	GLuint indices[6] = {0, 1, 3, 1, 2, 3};

	glBindVertexArray(VAOs[ShapeArrayObject::Quad]);

	glEnableVertexAttribArray(0);
	///Need to modify binding when adding color
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ShapeArrayObject::Quad]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint IndexBuffer;
	glGenBuffers(1, &IndexBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(0);

	glBindVertexArray(0); // Disable our Vertex Buffer Object 
}

void OpenGLRenderer::SetWindowSize(int x, int y)
{
	//set dimensions
	width = x;
	height = y;
}

void OpenGLRenderer::SetContextHandle(HDC _handle)
{
	//set handle
	contextHandle = _handle;
}

void OpenGLRenderer::SetViewport(int x, int y, int width, int height)
{
	//set viewport
   // glViewport(x, y, width, height);

	////update projection matrix
 //   glMatrixMode(GL_PROJECTION);
 //   glLoadIdentity();
 //   gluPerspective(45.0,(float)width/(float)height, 1, 1000);
}

void OpenGLRenderer::SwapBuffer()
{
	//swap the buffers
	SwapBuffers(contextHandle);
}

void OpenGLRenderer::ClearRenderer()
{
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}