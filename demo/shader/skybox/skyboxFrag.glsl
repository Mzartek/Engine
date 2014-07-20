#version 330

uniform samplerCube cubeMap;

in vec3 outTexCoord;

layout(location = 0) out uvec3 outMaterial;

void main(void)
{
	outMaterial =
		uvec3(0xFF000000 & uvec3(ivec3(texture(cubeMap, outTexCoord) * 255) << 24)) |
		uvec3(0x00FF0000 & (ivec3(255, 255, 255) << 16)) |
		uvec3(0x0000FFFF & ivec3(0.0, 0.0, 0.0));
}
