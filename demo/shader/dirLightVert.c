#version 330

struct dirLight
{
	vec3 color;
	vec3 rayDir;
	mat4 shadowMatrix;
};

uniform vec3 camPosition;
uniform vec3 lightColor;
uniform vec3 lightDirection;
uniform mat4 shadowMatrix;

layout(location = 0) in vec2 vertexArray;
layout(location = 1) in vec2 textureArray;

out vec2 texCoord;
out vec3 eyePos;
out dirLight light;

void main(void)
{
	gl_Position = vec4(vertexArray, 0.0, 1.0);
	texCoord = textureArray;
	eyePos = camPosition;
	light.color = lightColor;
	light.rayDir = lightDirection;
	light.shadowMatrix = shadowMatrix;
}
