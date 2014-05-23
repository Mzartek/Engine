#version 330

uniform sampler2D colorTexture;

in vec3 position;
in vec2 texCoord;
in vec3 normal;

layout(location = 0) out vec3 outPosition;
layout(location = 1) out vec2 outTexCoord;
layout(location = 2) out vec3 outNormal;
layout(location = 3) out vec4 outDiffuse;

void main(void)
{
	outPosition = position;
	outTexCoord = texCoord;
	outNormal = normalize(normal);
	outDiffuse = texture(colorTexture, texCoord);
}
