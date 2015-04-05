#version 440

// From GBuffer
uniform sampler2D normalTexture;
uniform usampler2D materialTexture;
uniform sampler2D depthTexture;

// ShadowMap
uniform sampler2DShadow shadowMap0;
uniform sampler2DShadow shadowMap1;
uniform sampler2DShadow shadowMap2;

layout(binding = 0) uniform mainInfoBuffer
{
	mat4 IVPMatrix;
	uvec2 screen;
	vec3 camPosition;
	bool withShadowMapping;
};

layout(binding = 1) uniform lightInfoBuffer
{
	vec3 lightColor;
	vec3 lightDirection;
	mat4 shadowMatrix[3];
};

layout(location = 0) out vec4 outLight;

vec3 getPosition(vec2 fragCoord)
{
	float depth = texelFetch(depthTexture, ivec2(fragCoord), 0).x * 2.0 - 1.0;
	vec4 tmp1 = vec4(fragCoord/screen * 2.0 - 1.0, depth, 1.0);
	vec4 tmp2 = IVPMatrix * tmp1;
	return tmp2.xyz / tmp2.w;
}

float lookUp(vec4 coord, vec2 offSet, ivec2 texSize, sampler2DShadow shadowMap)
{
	coord.x = 0.5f + (coord.x / coord.w * 0.5f);
	coord.y = 0.5f + (coord.y / coord.w * 0.5f);
	coord.z = 0.5f + ((coord.z - 0.005) / coord.w * 0.5f);

	coord.x += offSet.x * (1.0/texSize.x);
	coord.y += offSet.y * (1.0/texSize.y);

	if(coord.x > 1.0 || coord.x < 0.0 || coord.y > 1.0 || coord.y < 0.0)
		return 1.0;
	return texture(shadowMap, coord.xyz);
}

float calcShadow(vec4 coord, float pcf, sampler2DShadow shadowMap)
{
	float a, x, y, shadow = 0.0;
	ivec2 texSize = textureSize(shadowMap, 0);

	a = (pcf-1.0)/2.0;
	for(x=-a ; x<=a ; x+=1.0)
	  for(y=-a ; y<=a ; y+=1.0)
		  shadow += lookUp(coord, vec2(x, y), texSize, shadowMap);
	shadow /= (pcf*pcf);

	return shadow;
}

vec4 calcLight(vec4 diffColor, vec4 specColor, vec3 N, vec3 L, vec3 V, float shininess)
{
	vec3 H = normalize(L + V);
	vec4 diff = max(dot(N, L), 0.0) * diffColor;
	vec4 spec = pow(max(dot(N, H), 0.0), shininess) * specColor;
	return diff + spec;
}

void main(void)
{
	vec3 position = getPosition(gl_FragCoord.xy);
	vec4 normal = texelFetch(normalTexture, ivec2(gl_FragCoord.xy), 0);
	uvec4 material = texelFetch(materialTexture, ivec2(gl_FragCoord.xy), 0);

	vec4 diffColor = unpackUnorm4x8(material.z) * vec4(lightColor, 1.0);
	vec4 specColor = unpackUnorm4x8(material.w) * vec4(lightColor, 1.0);
	
	vec3 cam_minus_pos = camPosition - position;
	float shadow = 1.0;
	if (withShadowMapping)
	{
		float distance = length(cam_minus_pos);
		if      (distance < 25) shadow = calcShadow(shadowMatrix[0] * vec4(position, 1.0), 3.0, shadowMap0);
		else if (distance < 50) shadow = calcShadow(shadowMatrix[1] * vec4(position, 1.0), 1.0, shadowMap1);
		else                    shadow = calcShadow(shadowMatrix[2] * vec4(position, 1.0), 1.0, shadowMap2);
	}
	
	outLight = calcLight(diffColor, specColor, normal.xyz, normalize(-lightDirection), normalize(cam_minus_pos), normal.w) * shadow;
}
