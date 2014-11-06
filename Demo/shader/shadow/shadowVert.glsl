#version 440

layout (binding = 0) uniform matrixBuffer
{
	mat4 MVP;
	mat4 normalMatrix;
};

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;

out VertexData
{
	vec2 texCoord;
} VertOut;

void main()
{
	gl_Position = MVP * vec4(vertex, 1.0);
	VertOut.texCoord = texCoord;
}
