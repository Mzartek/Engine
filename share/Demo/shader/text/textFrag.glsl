#version 440

uniform sampler2D textTex;

in VertexData
{
	vec2 texCoord;
} FragIn;

layout(location = 0) out vec4 fragColor;

void main(void)
{
	fragColor = texture(textTex, vec2(FragIn.texCoord.x, 1.0 - FragIn.texCoord.y));
}
