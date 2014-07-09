#version 330

uniform vec3 camPosition;
uniform vec3 lightColor;
uniform vec3 lightDirection;
uniform mat4 shadowMatrix;

// From GBuffer
uniform sampler2D positionTexture;
uniform sampler2D normalTexture;

// From ShadowMap
uniform sampler2DShadow shadowMap;

// Form LBuffer
uniform usampler2D lightTexture;

layout(location = 0) out uvec4 outLightTexture;


float lookUp(sampler2DShadow tex, vec4 coord, vec2 offSet, ivec2 texSize)
{
	return textureProj(tex, vec4(coord.x + (offSet.x * (1.0/texSize.x)), coord.y + (offSet.y * (1.0/texSize.y)), coord.z-0.005, coord.w));
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

void calcDirLight(vec3 N, vec3 eyeVec, float shininess, float shadow) // N need to be normalize
{
	vec3 L, E, R;
	uvec4 srcLight = texelFetch(lightTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0);
	vec4 cDiff = vec4(0x0000FFFF & (ivec4(srcLight) >> 16)) / 65535;
	vec4 cSpec = vec4(0x0000FFFF & ivec4(srcLight)) / 65535;
	float cosTheta, specular;
  
	L = normalize(lightDirection);
	
	cosTheta = dot(-L,N);
	if(cosTheta > 0.0 && shadow != 0.0)
	{
		E = normalize(eyeVec);
		R = reflect(L, N);

		specular = pow(max(dot(R, E), 0.0), shininess);
      
		cDiff = clamp(cDiff + (vec4(lightColor, 1.0) * cosTheta * shadow), 0.0, 1.0);
		cSpec = clamp(cSpec + (vec4(lightColor, 1.0) * specular * shadow), 0.0, 1.0);
	}

	outLightTexture = (0xFFFF0000 & uvec4(ivec4(cDiff * 65535) << 16)) | uvec4(0x0000FFFF & ivec4(cSpec * 65535));
}

void main(void)
{
	vec3 position = texelFetch(positionTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0).xyz;
	vec4 normal = texelFetch(normalTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0);
	float s = 1.0;

	s = calcShadow(shadowMap, shadowMatrix * vec4(position, 1.0), 1.0);
	calcDirLight(normal.xyz, camPosition - position, normal.w, s);
}
