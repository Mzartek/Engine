#version 330

// From GBuffer
uniform sampler2D normalTexture;
uniform usampler2D materialTexture;
uniform sampler2D depthTexture;

// From ShadowMap
uniform sampler2DShadow shadowMap;
uniform mat4 shadowMatrix;

// GLobals
uniform uvec2 screen;
uniform mat4 IVP;
uniform vec3 camPosition;
uniform vec3 lightColor;
uniform vec3 lightDirection;

layout(location = 0) out uvec3 outMaterial;

vec3 getPosition(void)
{
  vec2 texCoord = vec2(gl_FragCoord.x/screen.x, gl_FragCoord.y/screen.y);
  vec4 tmp1 = vec4(texCoord * 2.0f - 1.0f, texture(depthTexture, texCoord).z * 2.0f - 1.0f, 1.0f);
  vec4 tmp2 = IVP * tmp1;
  return tmp2.xyz / tmp2.w;
}

float lookUp(sampler2DShadow tex, vec4 coord, vec2 offSet, ivec2 texSize)
{
	if (coord.x > 1.0 || coord.x < 0.0 || coord.y > 1.0 || coord.y < 0.0)
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

struct light
{
    vec3 diff;
    vec3 spec;
};

light calcDirLight(vec3 N, vec3 eyeVec, float shininess, float shadow) // N need to be normalize
{
	vec3 L, E, R;
	float cosTheta, specular;
	light res;

	res.diff = vec3(0.0, 0.0, 0.0);
	res.spec = vec3(0.0, 0.0, 0.0);

	L = normalize(lightDirection);

	cosTheta = dot(-L,N);
	if(cosTheta > 0.0 && shadow != 0.0)
	{
		E = normalize(eyeVec);
		R = reflect(L, N);

		specular = pow(max(dot(R, E), 0.0), shininess);

		res.diff += lightColor * cosTheta * shadow;
		res.spec += lightColor * specular * shadow;
	}

	return res;
}

void main(void)
{
	vec3 position, finalColor, matAmbient, matDiffuse, matSpecular;
	vec4 normal;
	uvec3 material;
	float s;
	light l;

	position = getPosition();
	normal = texelFetch(normalTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0);
	material = texelFetch(materialTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0).xyz;
	finalColor = vec3(0x000000FF & (ivec3(material) >> 24)) / 255;
	matAmbient = vec3(0x000000FF & (ivec3(material) >> 16)) / 255;
	matDiffuse = vec3(0x000000FF & (ivec3(material) >> 8)) / 255;
	matSpecular = vec3(0x000000FF & ivec3(material)) / 255;

	s = calcShadow(shadowMap, shadowMatrix * vec4(position, 1.0), 1.0);
	l = calcDirLight(normal.xyz, camPosition - position, normal.w, s);
	finalColor *= matAmbient + (matDiffuse * l.diff) + (matSpecular * l.spec);
	finalColor = clamp(finalColor, 0.0, 1.0);

	outMaterial =
		uvec3(0xFF000000 & uvec3(ivec3(finalColor * 255) << 24)) |
		uvec3(0x00FF0000 & (ivec3(matAmbient * 255) << 16)) |
		uvec3(0x0000FF00 & (ivec3(matDiffuse * 255) << 8)) |
		uvec3(0x000000FF & ivec3(matSpecular * 255));
}
