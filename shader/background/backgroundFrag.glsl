#version 440

uniform usampler2D materialTexture;
uniform sampler2D lightTexture;

layout(location = 0) out vec4 fragColor;

void main(void)
{
	uvec4 material = texelFetch(materialTexture, ivec2(gl_FragCoord.xy), 0);
	vec4 light = texelFetch(lightTexture, ivec2(gl_FragCoord.xy), 0);
	
	fragColor = unpackUnorm4x8(material.x) * (unpackUnorm4x8(material.y) + light);
	fragColor = clamp(fragColor, 0.0, 1.0);
}