#version 440

uniform sampler2D colorTexture ;
uniform sampler2D NMTexture;

layout(binding = 1) uniform materialBuffer
{
	vec4 matAmbient;
	vec4 matDiffuse;
	vec4 matSpecular;
	float shininess;
};

in VertexData
{
	vec2 texCoord;
	mat3 TBN;
} FragIn;

layout(location = 0) out vec4 outNormal;
layout(location = 1) out uvec4 outMaterial;

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
		outMaterial.x = packUnorm4x8(color);
		outMaterial.y = packUnorm4x8(matAmbient);
		outMaterial.z = packUnorm4x8(matDiffuse);
		outMaterial.w = packUnorm4x8(matSpecular);
		gl_FragDepth = gl_FragCoord.z;
    }
    else
		gl_FragDepth = 1.0;
}
