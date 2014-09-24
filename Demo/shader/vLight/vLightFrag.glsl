#version 440

// From GBuffer
uniform sampler2D normalTexture;
uniform usampler2D materialTexture;
uniform sampler2D depthTexture;

layout(binding = 0) uniform IVPMatrixBuffer
{
	mat4 IVPMatrix;
};

layout(binding = 1) uniform screenBuffer
{
	uvec2 screen;
};

layout(binding = 2) uniform cameraBuffer
{
	vec3 camPosition;
};

layout(binding = 3) uniform vDirLightInfo
{
	vec3 dlColor[20];
	vec3 dlDirection[20];
	uint numDirLight;
};

layout(binding = 4) uniform vSpotLightInfo
{
	vec3 slColor[20];
	vec3 slPosition[20];
	vec3 slDirection[20];
	float slSpotCutOff[20];
	uint numSpotLight;
};

layout(location = 0) out vec4 outLight;

vec3 getPosition(vec2 fragCoord)
{
	float depth = texelFetch(depthTexture, ivec2(fragCoord), 0).x * 2.0 - 1.0;
	vec4 tmp1 = vec4(fragCoord/screen * 2.0 - 1.0, depth, 1.0);
	vec4 tmp2 = IVPMatrix * tmp1;
	return tmp2.xyz / tmp2.w;
}

vec4 calcLight(vec4 diffColor, vec4 specColor, vec3 N, vec3 L, vec3 V, float shininess)
{
	vec3 R = reflect(-L, N);
	vec4 diff = max(dot(N, L), 0.0) * diffColor;
	vec4 spec = pow(max(dot(R, V), 0.0), shininess) * specColor;
	return diff + spec;
}

void main(void)
{
	outLight = vec4(0.0, 0.0, 0.0, 0.0);

	vec3 position = getPosition(gl_FragCoord.xy);
	vec4 normal = texelFetch(normalTexture, ivec2(gl_FragCoord.xy), 0);
	uvec4 material = texelFetch(materialTexture, ivec2(gl_FragCoord.xy), 0);

	vec4 diffColor = unpackUnorm4x8(material.z);
	vec4 specColor = unpackUnorm4x8(material.w);
	
	vec3 L, V = normalize(camPosition - position);
	float cos_cur_angle, cos_outer_cone_angle, cos_inner_cone_angle, cos_inner_minus_outer_angle, spot;
	
	uint i;
	for(i=0; i<numDirLight; i++)
	{
		L = normalize(-dlDirection[i]);
		outLight += calcLight(diffColor * vec4(dlColor[i], 1.0), specColor * vec4(dlColor[i], 1.0), normal.xyz, L, V, normal.w);
	}
	for(i=0; i<numSpotLight; i++)
	{
		L = normalize(slPosition[i] - position);
		cos_cur_angle = dot(-L, normalize(slDirection[i]));
		cos_outer_cone_angle = cos(radians(slSpotCutOff[i]));
		cos_inner_cone_angle = cos_outer_cone_angle + 0.01;
		cos_inner_minus_outer_angle = cos_inner_cone_angle - cos_outer_cone_angle;
		spot = clamp((cos_cur_angle - cos_outer_cone_angle) / cos_inner_minus_outer_angle, 0.0, 1.0);
		outLight += calcLight(diffColor * vec4(dlColor[i], 1.0), specColor * vec4(dlColor[i], 1.0), normal.xyz, L, V, normal.w) * spot;
	}
}
