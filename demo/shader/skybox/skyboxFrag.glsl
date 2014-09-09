#version 330

uniform samplerCube cubeMap;

in VertexData
{
	vec3 texCoord;
} FragIn;

out vec4 fragColor;

uvec4 pack(ivec4 a, ivec4 b, ivec4 c, ivec4 d)
{
	uvec4 res = 
		uvec4(0xFF000000 & uvec4(a << 24)) |
		uvec4(0x00FF0000 & (b << 16)) |
		uvec4(0x0000FF00 & (c << 8)) |
		uvec4(0x000000FF & d);

	return res;
}

void main(void)
{
	fragColor = texture(cubeMap, vec3(FragIn.texCoord.x, -FragIn.texCoord.y, FragIn.texCoord.z));
}
