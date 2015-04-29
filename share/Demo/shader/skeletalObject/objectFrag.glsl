#version 440

uniform sampler2D diffuseTex;
uniform sampler2D specularTex;
uniform sampler2D ambiantTex;
uniform sampler2D emissiveTex;
uniform sampler2D shininessTex;
uniform sampler2D opacityTex;
uniform sampler2D bumpMap;
uniform sampler2D normalMap;
uniform sampler2D displacementMap;
uniform sampler2D lightMap;
uniform samplerCube reflectionTex;

layout(binding = 2) uniform materialBuffer
{
	vec3 matDiffuse;
	vec3 matSpecular;
	vec3 matAmbient;
	vec3 matEmissive;
	float matShininess;
	float matOpacity;
};

layout(binding = 3) uniform stateBuffer
{
	bool hasDiffuseTexture;
	bool hasSpecularTexture;
	bool hasAmbientTexture;
	bool hasEmissiveTexture;
	bool hasShininessTexture;
	bool hasOpacityTexture;
	bool hasBumpMap;
	bool hasNormalMap;
	bool hasDisplacementMap;
	bool hasLightMap;
};

in VertexData
{
	vec2 texCoord;
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
} FragIn;

layout(location = 0) out vec4 outNormal;
layout(location = 1) out uvec4 outMaterial;

vec4 getColor(void)
{
	if (hasDiffuseTexture)
		return texture(diffuseTex, vec2(FragIn.texCoord.x, 1.0f - FragIn.texCoord.y));
	else
		return vec4(1.0, 1.0, 1.0, 1.0);
}

vec3 getNormal(void)
{
	if (hasNormalMap)
	{
		mat3 TBN = mat3(FragIn.tangent, FragIn.bitangent, FragIn.normal);
		vec3 bumpMapNormal = texture(normalMap, vec2(FragIn.texCoord.x, 1.0f - FragIn.texCoord.y)).xyz;

		return TBN * (bumpMapNormal * 2.0 - 1.0);
	}
	else
		return FragIn.normal;
}

void main(void)
{
	vec4 color = getColor();
	vec3 normal = getNormal();

	if(color.a > 0.5)
	{
		outNormal = vec4(normal, matShininess);
		outMaterial.x = packUnorm4x8(color);
		outMaterial.y = packUnorm4x8(vec4(matAmbient, matOpacity));
		outMaterial.z = packUnorm4x8(vec4(matDiffuse, matOpacity));
		outMaterial.w = packUnorm4x8(vec4(matSpecular, matOpacity));
		gl_FragDepth = gl_FragCoord.z;
	}
	else
		discard;
}
