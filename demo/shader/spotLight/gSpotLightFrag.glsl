#version 330

// From GBuffer
uniform sampler2D normalTexture;
uniform usampler2D materialTexture;
uniform sampler2D depthTexture;

// ShadowMap
uniform sampler2DShadow shadowMap;

// Matrix
uniform mat4 shadowMatrix;
uniform mat4 IVPMatrix;

// Screen Info
uniform uvec2 screen;

// Cam Info
uniform vec3 camPosition;

// Light info
uniform lightInfo
{
	vec3 lightColor;
	vec3 lightPosition;
	vec3 lightDirection;
	float lightSpotCutOff;
	bool withShadowMapping;
};

layout(location = 0) out vec4 outNormal;
layout(location = 1) out uvec4 outMaterial;

vec3 getPosition(void)
{
    float depth = texelFetch(depthTexture, ivec2(gl_FragCoord.xy), 0).x;
    vec4 tmp1 = vec4(gl_FragCoord.xy/screen.xy * 2.0f - 1.0f, depth * 2.0f - 1.0f, 1.0f);
    vec4 tmp2 = IVPMatrix * tmp1;
    return tmp2.xyz / tmp2.w;
}

float lookUp(sampler2DShadow tex, vec4 coord, vec2 offSet, ivec2 texSize)
{
	if (coord.x > 1.0 || coord.x < 0.0 || coord.y > 1.0 || coord.y < 0.0)
		return 1.0;
	return texture(tex, vec3(coord.x + (offSet.x * (1.0/texSize.x)), coord.y + (offSet.y * (1.0/texSize.y)), coord.z-0.005));
}

float calcShadow(sampler2DShadow tex, vec4 coord, float pcf)
{
	float a, x, y, shadow = 0.0;

	a = (pcf-1.0)/2.0;
	for(x=-a ; x<=a ; x+=1.0)
	  for(y=-a ; y<=a ; y+=1.0)
		  shadow += lookUp(tex, coord, vec2(x, y), textureSize(tex, 0));
	shadow /= (pcf*pcf);

	return shadow;
}

struct light
{
    vec3 diff;
    vec3 spec;
};

light calcSpotLight(vec3 N, vec3 eyeVec, vec3 position, float shininess, float shadow) // N need to be normalize
{
	vec3 L, D, E, R;
	float cos_cur_angle, cos_inner_cone_angle, cos_outer_cone_angle, cos_inner_minus_outer_angle;
	float cosTheta, spot, specular;
	light res;

	res.diff = vec3(0.0, 0.0, 0.0);
	res.spec = vec3(0.0, 0.0, 0.0);

	L = normalize(position - lightPosition);

	cosTheta = dot(-L,N);
	if(cosTheta > 0.0 && shadow != 0.0)
	{
		D = normalize(lightDirection);
		E = normalize(eyeVec);
		R = reflect(L, N);

		cos_cur_angle = dot(L, D);
		cos_outer_cone_angle = cos(radians(lightSpotCutOff));
		cos_inner_cone_angle = cos_outer_cone_angle + 0.01;
		cos_inner_minus_outer_angle = cos_inner_cone_angle - cos_outer_cone_angle;
		spot = clamp((cos_cur_angle - cos_outer_cone_angle) / cos_inner_minus_outer_angle, 0.0, 1.0);

		specular = pow(max(dot(R, E), 0.0), shininess);

		res.diff += lightColor * cosTheta * spot * shadow;
		res.spec += lightColor * specular * spot * shadow;
	}

	return res;
}

void main(void)
{
	vec3 position = getPosition();
	vec4 normal = texelFetch(normalTexture, ivec2(gl_FragCoord.xy), 0);
	uvec4 material = texelFetch(materialTexture, ivec2(gl_FragCoord.xy), 0);
	vec4 finalColor = vec4(0x000000FF & (ivec4(material) >> 24)) / 255;
	vec4 matAmbient = vec4(0x000000FF & (ivec4(material) >> 16)) / 255;
	vec4 matDiffuse = vec4(0x000000FF & (ivec4(material) >> 8)) / 255;
	vec4 matSpecular = vec4(0x000000FF & ivec4(material)) / 255;
	
	float s = 1.0;
	if (withShadowMapping)
		s = calcShadow(shadowMap, shadowMatrix * vec4(position, 1.0), 1.0);
	light l;
	if (withShadowMapping)
		l = calcSpotLight(normal.xyz, camPosition - position, position, normal.w, s);
	finalColor *= matAmbient + (matDiffuse * vec4(l.diff, 1.0)) + (matSpecular * vec4(l.spec, 1.0));
	finalColor = clamp(finalColor, 0.0, 1.0);
	
	outNormal = normal;
	outMaterial =
		uvec4(0xFF000000 & uvec4(ivec4(finalColor * 255) << 24)) |
		uvec4(0x00FF0000 & (ivec4(255, 255, 255, 255) << 16)) |
		uvec4(0x0000FF00 & (ivec4(matDiffuse * 255) << 8)) |
		uvec4(0x000000FF & ivec4(matSpecular * 255));
}
