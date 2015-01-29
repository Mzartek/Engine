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
    vec3 camTarget;
};

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;

out VertexData
{
	vec2 texCoord;
	vec3 normal;
} VertOut;

void main(void)
{
    mat4 modelViewMatrix = viewMatrix * modelMatrix;

    modelViewMatrix[0][0] = 1;
    modelViewMatrix[0][1] = 0;
    modelViewMatrix[0][2] = 0;

    modelViewMatrix[2][0] = 0;
    modelViewMatrix[2][1] = 0;
    modelViewMatrix[2][2] = 1;

	gl_Position = projectionMatrix * modelViewMatrix * vec4(vertex, 1.0);

	VertOut.texCoord = texCoord;
	VertOut.normal = normalize(vec3(camPosition.x, 0, camPosition.z) - vec3(modelMatrix[3][0], 0, modelMatrix[3][2]));
}
