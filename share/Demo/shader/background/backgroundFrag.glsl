#version 440

uniform usampler2D materialTexture;
uniform sampler2D lightTexture;

layout(location = 0) out vec4 fragColor;

in VertexData
{
	vec2 texCoord;
} FragIn;

void main(void)
{
	uvec4 material = texture(materialTexture, FragIn.texCoord);
	vec4 light = texture(lightTexture, FragIn.texCoord);
	
	fragColor = unpackUnorm4x8(material.x) * (unpackUnorm4x8(material.y) + light);
	fragColor = clamp(fragColor, 0.0, 1.0);
}