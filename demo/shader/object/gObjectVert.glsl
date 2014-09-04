#version 330

uniform mat4 MVP;
uniform mat4 normalMatrix;

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;

out VertexData
{
	vec2 texCoord;
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
} VertOut;

void main(void)
{
	gl_Position =  MVP * vec4(vertex, 1.0);

	VertOut.texCoord = texCoord;
	VertOut.normal = normalize(mat3(normalMatrix) * normal);
	VertOut.tangent = normalize(mat3(normalMatrix) * tangent);
	VertOut.bitangent = cross(VertOut.normal, VertOut.tangent);
}
