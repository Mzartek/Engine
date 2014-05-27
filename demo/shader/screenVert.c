#version 330

uniform vec4 color;

layout(location = 0) in vec2 vertexArray;
layout(location = 1) in vec2 textureArray;

out vec4 outColor;

void main(void)
{
	gl_Position = vec4(vertexArray, 0.0, 1.0);
	
	outColor = color;
}
