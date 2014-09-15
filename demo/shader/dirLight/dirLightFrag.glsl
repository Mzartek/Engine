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
	vec3 lightDirection;
	bool withShadowMapping;
};

layout(location = 0) out vec4 outLight;

uvec4 pack(ivec4 a, ivec4 b, ivec4 c, ivec4 d)
{
	uvec4 res = 
		uvec4(0xFF000000 & uvec4(a << 24)) |
		uvec4(0x00FF0000 & (b << 16)) |
		uvec4(0x0000FF00 & (c << 8)) |
		uvec4(0x000000FF & d);

	return res;
}

ivec4 unpack(uvec4 a, int v)
{
	return (0x000000FF & (ivec4(a) >> (v * 8)));
}

vec3 getPosition(vec2 fragCoord)
{
	float depth = texelFetch(depthTexture, ivec2(fragCoord), 0).x;
	vec4 tmp1 = vec4(fragCoord/screen * 2.0 - 1.0, depth * 2.0 - 1.0, 1.0);
	vec4 tmp2 = IVPMatrix * tmp1;
	return tmp2.xyz / tmp2.w;
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

vec4 calcDirLight(vec4 diffColor, vec4 specColor, vec3 N, vec3 eyeVec, float shininess, float shadow) // N need to be normalize
{
	vec3 L, V, R;
	vec4 diff, spec;

	diff = vec4(0.0, 0.0, 0.0, 0.0);
	spec = vec4(0.0, 0.0, 0.0, 0.0);

	L = normalize(-lightDirection);
	V = normalize(eyeVec);
	R = reflect(-L, N);

	diff = max(dot(N, L), 0.0) * diffColor * shadow;
	spec = pow(max(dot(R, V), 0.0), shininess) * specColor * shadow;

	return diff + spec;
}

void main(void)
{
	vec3 position = getPosition(gl_FragCoord.xy);
	vec4 normal = texelFetch(normalTexture, ivec2(gl_FragCoord.xy), 0);
	uvec4 material = texelFetch(materialTexture, ivec2(gl_FragCoord.xy), 0);

	vec4 diffColor = (vec4(unpack(material, 1)) / 255) * vec4(lightColor, 1.0);
	vec4 specColor = (vec4(unpack(material, 0)) / 255) * vec4(lightColor, 1.0);
	
	float s = 1.0;
	if (withShadowMapping)
		s = calcShadow(shadowMatrix * vec4(position, 1.0), 1.0);
	outLight = calcDirLight(diffColor, specColor, normal.xyz, camPosition - position, normal.w, s);
}