#version 330

uniform samplerCube cubeMap;

in vec3 outTexCoord;

out vec4 fragColor;

void main(void)
{
  fragColor = texture(cubeMap, outTexCoord);
}
