#version 330

layout(location = 0) in vec2 vertexArray;

void main(void)
{
	gl_Position = vec4(vertexArray, 0.0, 1.0);
}
