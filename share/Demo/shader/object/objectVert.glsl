#version 440

layout (binding = 0) uniform matrixBuffer
{
	mat4 MVP;
	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 modelMatrix;
	mat4 normalMatrix;
};

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;

out VertexData
{
	vec2 texCoord;
	mat3 TBN;
} VertOut;

void main(void)
{
	gl_Position = MVP * vec4(vertex, 1.0);

	vec3 N = (normalMatrix * vec4(normal, 0.0)).xyz;
	vec3 T = (normalMatrix * vec4(tangent, 0.0)).xyz;
	vec3 B = cross(N, T);

	VertOut.texCoord = texCoord;
	VertOut.TBN = mat3(T, B, N);
}
