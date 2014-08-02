#version 330

uniform samplerCube cubeMap;

in vec3 outTexCoord;

layout(location = 0) out uvec4 outMaterial;

void main(void)
{
	outMaterial =
		uvec4(0xFF000000 & uvec4(ivec4(texture(cubeMap, outTexCoord) * 255) << 24)) |
		uvec4(0x00FF0000 & (ivec4(255, 255, 255, 255) << 16)) |
		uvec4(0x0000FFFF & ivec4(0.0, 0.0, 0.0, 0.0));
}
