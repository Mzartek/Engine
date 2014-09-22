#version 440

layout (binding = 0) uniform MVPMatrixBuffer
{
	mat4 MVP;
};

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 texCoord;

out VertexData
{
	vec2 texCoord;
} VertOut;

void main()
{
	gl_Position = MVP * vec4(vertex, 1.0);
	VertOut.texCoord = texCoord;
}
