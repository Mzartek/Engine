#version 330

uniform mat4 MVP;
uniform mat3 normalMatrix;

out vec2 vtexCoord;
out vec3 vnormal;

layout(location = 0) in vec3 vertexArray;
layout(location = 1) in vec2 textureArray;
layout(location = 2) in vec3 normalArray;

void main(void)
{
	gl_Position =  MVP * vec4(vertexArray, 1.0);

	vtexCoord = textureArray;
	vnormal = normalMatrix * normalArray;
}
