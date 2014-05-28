#version 330

uniform sampler2D colorTexture;

in vec4 position;
in vec2 texCoord;
in vec3 normal;
in float shininess;

layout(location = 0) out vec4 outPositionTexture;
layout(location = 1) out vec4 outNormalTexture;
layout(location = 2) out vec4 outShininessTexture;
layout(location = 3) out vec4 outDiffuseTexture;

void main(void)
{
	outPositionTexture = position;
	outNormalTexture = vec4(normalize(normal), 1.0);
	outShininessTexture = vec4(shininess, 0.0, 0.0, 1.0);
	outDiffuseTexture = texture(colorTexture, texCoord);
}
