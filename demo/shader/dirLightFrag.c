#version 330

struct dirLight
{
	vec3 color;
	vec3 rayDir;
	mat4 shadowMatrix;
};

// From GBuffer
uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D shininessTexture;

// From ShadowMap
uniform sampler2DShadow shadowMap;

// Form LBuffer
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

in vec2 texCoord;
in vec3 eyePos;
in dirLight light;

layout(location = 0) out vec4 outDiffuseTexture;
layout(location = 1) out vec4 outSpecularTexture;


float lookUp(sampler2DShadow tex, vec4 coord, vec2 offSet, ivec2 texSize)
{
	return textureProj(tex, vec4(coord.x + (offSet.x * (1.0/texSize.x)), coord.y + (offSet.y * (1.0/texSize.y)), coord.z-0.005, coord.w));
}

float calcShadow(sampler2DShadow tex, vec4 coord, float pcf)
{
	ivec2 texSize = textureSize(tex, 0);
	float a, x, y, shadow = 0.0;

	a = (pcf-1.0)/2.0;
	for(x=-a ; x<=a ; x+=1.0)
	  for(y=-a ; y<=a ; y+=1.0)
	    shadow += lookUp(tex, coord, vec2(x,y), texSize);
	shadow /= (pcf*pcf);

	return shadow;
}

void calcDirLight(vec3 N, vec3 eyeVec, float shininess, float shadow) // N need to be normalize
{
	vec3 L, E, R;
	float cosTheta, specular;

	outDiffuseTexture = texture(diffuseTexture, texCoord);
	outSpecularTexture = texture(specularTexture, texCoord);
  
	L = normalize(light.rayDir);
	
	cosTheta = dot(-L,N);
	if(cosTheta > 0.0 && shadow != 0.0)
	{
		E = normalize(eyeVec);
		R = reflect(L, N);

		specular = pow(max(dot(R, E), 0.0), shininess);
      
		outDiffuseTexture += vec4(light.color, 1.0) * cosTheta * shadow;
		outSpecularTexture += vec4(light.color, 1.0) * specular * shadow;
	}
}

void main(void)
{
	vec3 position = texture(positionTexture, texCoord).xyz;
	vec3 normal = texture(normalTexture, texCoord).xyz;
	float shininess = texture(shininessTexture, texCoord).x;
	float s = 1.0;

	s = calcShadow(shadowMap, light.shadowMatrix * vec4(position, 1.0), 3.0);
	calcDirLight(normal, eyePos - position, shininess, s);
}
