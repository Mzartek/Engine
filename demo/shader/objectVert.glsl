#version 330

uniform mat4 MVP;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

out vec3 position;
out vec2 texCoord;
out vec3 normal;

layout(location = 0) in vec3 vertexArray;
layout(location = 1) in vec2 textureArray;
layout(location = 2) in vec3 normalArray;

void main(void)
{
	gl_Position =  MVP * vec4(vertexArray, 1.0);

	position = vec3(modelMatrix * vec4(vertexArray, 1.0));
	texCoord = textureArray;
	normal = normalMatrix * normalArray;
}
