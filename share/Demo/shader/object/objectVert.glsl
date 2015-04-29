#version 440

layout (binding = 0) uniform matrixBuffer
{
	mat4 MVP;
	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 modelMatrix;
	mat4 normalMatrix;
};

layout (binding = 1) uniform cameraBuffer
{
    vec3 camPosition;
    vec3 camForward;
	vec3 camLeft;
	vec3 camUp;
};

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
	gl_Position = MVP * vec4(vertex, 1.0);
	VertOut.texCoord = texCoord;
	VertOut.normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
	VertOut.tangent = normalize((normalMatrix * vec4(tangent, 0.0)).xyz);
	VertOut.bitangent = cross(VertOut.normal, VertOut.tangent);
}
