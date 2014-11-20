#version 440

layout (binding = 0) uniform matrixBuffer
{
	mat4 MVP;
	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 modelMatrix;
};

layout(location = 0) in vec3 particle;

out VertexData
{
	vec4 particle;
} VertOut;

void main(void)
{
	VertOut.particle = MVP * vec4(particle, 1.0);
}
