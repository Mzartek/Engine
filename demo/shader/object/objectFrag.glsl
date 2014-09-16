#version 330

uniform sampler2D colorTexture;
uniform sampler2D NMTexture;

uniform material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

in VertexData
{
	vec2 texCoord;
	mat3 TBN;
} FragIn;

layout(location = 0) out vec4 outNormal;
layout(location = 1) out uvec4 outMaterial;

uvec4 pack(ivec4 a, ivec4 b, ivec4 c, ivec4 d)
{
	uvec4 res =
		uvec4(0xFF000000 & uvec4(a << 24)) |
		uvec4(0x00FF0000 & (b << 16)) |
		uvec4(0x0000FF00 & (c << 8)) |
		uvec4(0x000000FF & d);

	return res;
}

vec3 CalcBumpedNormal(mat3 TBN, vec3 bumpMapNormal)
{
	return normalize(TBN * (bumpMapNormal * 2.0 - 1.0));
}

void main(void)
{
    vec4 color = texture(colorTexture, vec2(FragIn.texCoord.x, 1.0 - FragIn.texCoord.y));
	vec3 normal = CalcBumpedNormal(FragIn.TBN, texture(NMTexture, vec2(FragIn.texCoord.x, 1.0 - FragIn.texCoord.y)).xyz);

    if(color.a > 0.5)
    {
        outNormal = vec4(normal, shininess);
        outMaterial = pack(ivec4(color * 255), ivec4(ambient * 255), ivec4(diffuse * 255), ivec4(specular * 255));
		gl_FragDepth = gl_FragCoord.z;
    }
    else
		gl_FragDepth = 1.0;
}
