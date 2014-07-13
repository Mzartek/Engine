#version 330

uniform vec3 camPosition;
uniform vec3 lightColor;
uniform vec3 lightDirection;
uniform mat4 shadowMatrix;

// From GBuffer
uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform usampler2D materialTexture;

// From ShadowMap
uniform sampler2DShadow shadowMap;

layout(location = 0) out uvec3 outMaterial;

float lookUp(sampler2DShadow tex, vec4 coord, vec2 offSet, ivec2 texSize)
{
	if (coord.x > 1.0 || coord.y > 1.0 || coord.x < 0.0 || coord.y < 0.0)
		return 1.0;
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
	float cosTheta, specular;

	vec3 lightDiff = vec3(0.0, 0.0, 0.0);
	vec3 lightSpec = vec3(0.0, 0.0, 0.0);
  
	L = normalize(lightDirection);
	
	cosTheta = dot(-L,N);
	if(cosTheta > 0.0 && shadow != 0.0)
	{
		E = normalize(eyeVec);
		R = reflect(L, N);

		specular = pow(max(dot(R, E), 0.0), shininess);
      
		lightDiff += lightColor * cosTheta * shadow;
		lightSpec += lightColor * specular * shadow;
	}

	uvec3 material = texelFetch(materialTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0).xyz;
	vec3 finalColor = vec3(0x000000FF & (ivec3(material) >> 24)) / 255;
	vec3 matAmbient = vec3(0x000000FF & (ivec3(material) >> 16)) / 255;
	vec3 matDiffuse = vec3(0x000000FF & (ivec3(material) >> 8)) / 255;
	vec3 matSpecular = vec3(0x000000FF & ivec3(material)) / 255;

	finalColor *= matAmbient + (matDiffuse * lightDiff) + (matSpecular * lightSpec);
	finalColor = clamp(finalColor, 0.0, 1.0);

	outMaterial = 
		uvec3(0xFF000000 & uvec3(ivec3(finalColor * 255) << 24)) |
		uvec3(0x00FF0000 & (ivec3(matAmbient * 255) << 16)) |
		uvec3(0x0000FF00 & (ivec3(matDiffuse * 255) << 8)) |
		uvec3(0x000000FF & ivec3(matSpecular * 255));
}

void main(void)
{
	vec3 position = texelFetch(positionTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0).xyz;
	vec4 normal = texelFetch(normalTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0);
	float s = 1.0;

	s = calcShadow(shadowMap, shadowMatrix * vec4(position, 1.0), 1.0);
	calcDirLight(normal.xyz, camPosition - position, normal.w, s);
}
