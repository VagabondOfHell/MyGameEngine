#version 430 core


layout(location = 0) in vec3 vPosition;
uniform mat4 ModelView, WorldView, Projection;
void main()
{
	gl_Position = Projection * WorldView * ModelView * vec4(vPosition, 1);
}