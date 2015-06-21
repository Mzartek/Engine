#version 440

uniform sampler2D inputTexture;

in VertexData
{
	vec2 texCoord;
} FragIn;

layout(location = 0) out vec4 fragColor;

void main(void)
{
	fragColor = texture(inputTexture, FragIn.texCoord);
}
