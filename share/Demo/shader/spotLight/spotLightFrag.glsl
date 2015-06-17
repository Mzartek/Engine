#version 440

#define LIMIT 50

// From GBuffer
uniform sampler2D normalTexture;
uniform usampler2D materialTexture;
uniform sampler2D depthTexture;

// ShadowMap
uniform sampler2DShadow shadowMap;

layout(binding = 0) uniform mainInfoBuffer
{
	mat4 IVPMatrix;
	vec3 camPosition;
	bool withShadowMapping;
};

layout(binding = 1) uniform lightInfoBuffer
{
	vec3 lightColor;
	vec3 lightPosition;
	vec3 lightDirection;
	float lightSpotCutOff;
	float lightMaxDistance;
	mat4 shadowMatrix;
};

in VertexData
{
	vec2 texCoord;
} FragIn;

layout(location = 0) out vec4 outLight;

vec3 getPosition(void)
{
	float depth = texture(depthTexture, FragIn.texCoord).x * 2.0 - 1.0;
	vec4 tmp1 = vec4(FragIn.texCoord * 2.0 - 1.0, depth, 1.0);
	vec4 tmp2 = IVPMatrix * tmp1;
	return tmp2.xyz / tmp2.w;
}

bool checkInside(vec3 position, float distance, float angle)
{
	if (distance > lightMaxDistance)
		return false;
		
	if (angle > lightSpotCutOff)
		return false;
		
	return true;
}

float lookUp(vec4 coord, vec2 offSet, ivec2 texSize)
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

float calcShadow(vec4 coord, float pcf)
{
	float a, x, y, shadow = 0.0;
	ivec2 texSize = textureSize(shadowMap, 0);

	a = (pcf-1.0)/2.0;
	for(x=-a ; x<=a ; x+=1.0)
	  for(y=-a ; y<=a ; y+=1.0)
		  shadow += lookUp(coord, vec2(x, y), texSize);
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
	vec3 position = getPosition();
	vec3 L = lightPosition - position;
	float current_distance = length(L);
	L = normalize(L);
	float current_angle = acos(dot(-L, lightDirection));
	
	if (!checkInside(position, current_distance, current_angle))
		discard;
	
	vec4 normal = texture(normalTexture, FragIn.texCoord);
	uvec4 material = texture(materialTexture, FragIn.texCoord);

	vec4 diffColor = unpackUnorm4x8(material.z) * vec4(lightColor, 1.0);
	vec4 specColor = unpackUnorm4x8(material.w) * vec4(lightColor, 1.0);

	float shadow = 1.0;
	if (withShadowMapping)
		shadow = calcShadow(shadowMatrix * vec4(position, 1.0), 1.0);

	float spot = 1.0;
	float inner_distance = lightMaxDistance - LIMIT;
	if (current_distance >= inner_distance)
	{
	     float tmp = min(current_distance, lightMaxDistance) - inner_distance;
	     spot *= (LIMIT - tmp) / LIMIT;
	}

	outLight = calcLight(diffColor, specColor, normal.xyz, L, normalize(camPosition - position), normal.w) * shadow * spot;
}
