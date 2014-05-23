#version 330

uniform mat4 MVP, modelMatrix;
uniform mat3 normalMatrix;

layout(location = 0) in vec3 vertexArray;
layout(location = 1) in vec2 textureArray;
layout(location = 2) in vec3 normalArray;

out vec3 position;
out vec2 texCoord;
out vec3 normal;

void main(void)
{
	gl_Position =  MVP * vec4(vertexArray, 1.0);
	
	position = vec4(modelMatrix * vec4(vertexArray, 1.0)).xyz;
	texCoord = vec2(textureArray.x, 1.0 - textureArray.y);
	normal = normalMatrix * normalArray;
}
