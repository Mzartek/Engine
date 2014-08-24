#version 330

uniform samplerCube cubeMap;

in VertexData
{
	vec3 texCoord;
} FragIn;

layout(location = 0) out vec4 outNormal;
layout(location = 1) out uvec4 outMaterial;

void main(void)
{
	outNormal = vec4(0.0, 0.0, 0.0, 0.0);
	outMaterial =
		uvec4(0xFF000000 & uvec4(ivec4(texture(cubeMap, vec3(FragIn.texCoord.x, -FragIn.texCoord.y, FragIn.texCoord.z)) * 255) << 24)) |
		uvec4(0x00FF0000 & (ivec4(255, 255, 255, 255) << 16)) |
		uvec4(0x0000FFFF & ivec4(0.0, 0.0, 0.0, 0.0));
}
