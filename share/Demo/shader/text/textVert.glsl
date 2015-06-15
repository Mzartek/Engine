#version 440

layout(location = 0) in vec2 vertex;
layout(location = 1) in vec2 texture;

out VertexData
{
	vec2 texCoord;
} VertOut;

void main(void)
{
	gl_Position = vec4(vertex.xy * 2.0 - 1.0, 0.0, 1.0);
	VertOut.texCoord = texture;
}
