#version 330

uniform sampler2D colorTexture;

in vec2 texCoord;
in vec3 normal;

layout(location = 0) out vec3 outDiffuse;
layout(location = 1) out vec3 outNormal;

void main(void)
{
	gl_FragDepth = gl_FragCoord.z;
	outDiffuse = texture(colorTexture, texCoord).xyz;
	outNormal = normalize(normal);
}
