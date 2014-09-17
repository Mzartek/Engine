#version 330

uniform mat4 MVP;

layout(location = 0) in vec2 vertex;
layout(location = 1) in vec2 texture;

out VertexData
{
	vec2 texCoord;
} VertOut;

void main(void)
{
	gl_Position = MVP * vec4(vertex.xy, 0.0, 1.0);
	VertOut.texCoord = texture;
}
