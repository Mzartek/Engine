#version 330

uniform samplerCube cubeMap;

in vec3 outTexCoord;

layout(location = 0) out vec3 outPosition;
layout(location = 1) out vec4 outNormal;
layout(location = 2) out uvec4 outMaterial;

void main(void)
{
	outPosition = vec3(0.0, 0.0, 0.0);
	outNormal = vec4(0.0, 0.0, 0.0, 0.0);

	outMaterial =
		uvec4(0xFF000000 & uvec4(ivec4(texture(cubeMap, outTexCoord) * 255) << 24)) |
		uvec4(0, 0, 0, 0);
}
