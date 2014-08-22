#version 330

uniform sampler2D textTex;

in VertexData
{
	vec2 texCoord;
} FragIn;

out vec4 fragColor;

void main(void)
{
	fragColor = texture(textTex, FragIn.texCoord);
}
