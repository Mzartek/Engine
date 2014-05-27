#version 330

struct material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

uniform float screenWidth, screenHeight;
uniform mat4 MVP;
uniform vec4 matAmbient, matDiffuse, matSpecular;

layout(location = 0) in vec3 vertexArray;
layout(location = 1) in vec2 textureArray;

out float outScreenWidth, outScreenHeight;
out vec2 outTexCoord;
out material outMat;

void main(void)
{
	gl_Position = MVP * vec4(vertexArray, 1.0);
	outScreenWidth = screenWidth;
	outScreenHeight = screenHeight;
	outTexCoord = vec2(textureArray.x, 1.0 - textureArray.y);
	outMat.ambient = matAmbient;
	outMat.diffuse = matDiffuse;
	outMat.specular = matSpecular;
}
