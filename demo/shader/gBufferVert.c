#version 330

uniform mat4 MVP;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform float matShininess;

out vec4 position;
out vec2 texCoord;
out vec3 normal;
out float shininess;

layout(location = 0) in vec3 vertexArray;
layout(location = 1) in vec3 textureArray;
layout(location = 2) in vec3 normalArray;

void main(void)
{
	gl_Position =  MVP * vec4(vertexArray, 1.0);

	position = modelMatrix * vec4(vertexArray, 1.0);
	texCoord = vec2(textureArray.x, 1.0 - textureArray.y);
	normal = normalMatrix * normalArray;
	shininess = matShininess;
}
