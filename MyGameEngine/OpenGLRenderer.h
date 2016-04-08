#pragma once
#include "abstractrenderer.h"
#include <Windows.h>

#include "vgl.h"
#include "LoadShaders.h"

#include <gl/gl.h>
#include <gl/glu.h>

class OpenGLRenderer :
	public AbstractRenderer
{
private:
	int width, height;
	HDC contextHandle;

	enum ShapeArrayObject{Point, Line, Triangle, Quad, NumberOfShapes};
	enum BufferArrayObject{Position, Colour, NumberOfBuffers};

	GLuint shaderProgram;

	GLuint VAOs[4];
	GLuint Buffers[4];

	void RenderPoint();
	void RenderLine();
	void RenderTriangle();
	void RenderQuad();

public:
	OpenGLRenderer(void);
	virtual ~OpenGLRenderer(void);

	///<summary>Initializes the Open GL Renderer</summary>
	///<returns>True if successful, false for errors</returns>
	bool Initialize();

	///<summary>Renders a primitive within OpenGL Context</summary>
	///<param "primitive">The type of primitive to render at the origin</param>
	virtual void RenderPrimitive(PrimitiveType primitive);

	///<summary>Sets the window to the specified size</summary>
	///<param "wwidth">The width of the window</param>
	///<param "wheight">The height of the window</param>
	void SetWindowSize(int wwidth, int wheight);

	///<summary>Sets the window context handle</summary>
	///<param "handle">The HDC handle of the window to associate the OpenGL context to</param>
	void SetContextHandle(HDC handle);

	///<summary>Sets the viewport to the specified dimensions</summary>
	///<param "x">The x position of the viewport</param>
	///<param "y">The y position of the viewport</param>
	///<param "width">The width of the viewport</param>
	///<param "height">The height of the viewport</param>
	void SetViewport(int x, int y, int width, int height);

	///<summary>Tells OpenGL to swap its buffers for double buffering</summary>
	void SwapBuffer();

	void ClearRenderer();
};

