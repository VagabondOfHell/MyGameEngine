#pragma once
/*
	An abstract renderer to be inherited from to provide access to common rendering functions
*/

class AbstractRenderer
{
public:
	enum PrimitiveType {Point, Line, Triangle, Quad};

	virtual bool Initialize() = 0;

	//Renders a primitive to the screen 
	virtual void RenderPrimitive(PrimitiveType primitive) = 0;
	virtual void SwapBuffer() = 0;
	virtual void ClearRenderer() = 0;
};