#version 330

uniform mat4 MVP;
uniform mat4 normalMatrix;

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out VertexData
{
	vec2 texCoord;
	vec3 normal;
} VertOut;

void main(void)
{
	gl_Position =  MVP * vec4(vertex, 1.0);

	VertOut.texCoord = texCoord;
	VertOut.normal = mat3(normalMatrix) * normal;
}
