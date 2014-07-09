#version 330

uniform sampler2D colorTexture;
uniform float matShininess;

in vec4 position;
in vec2 texCoord;
in vec3 normal;

layout(location = 0) out vec4 outPositionTexture;
layout(location = 1) out vec4 outNormalTexture;
layout(location = 2) out vec4 outDiffuseTexture;

void main(void)
{
	outPositionTexture = position;
	outNormalTexture = vec4(normalize(normal), matShininess);
	outDiffuseTexture = texture(colorTexture, texCoord);
}
