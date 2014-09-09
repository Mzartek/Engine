#version 330

uniform mat4 MVP;

layout(location = 0) in vec3 vertex;

out VertexData
{
	vec3 texCoord;
} VertOut;

void main(void)
{
  gl_Position = MVP * vec4(vertex, 1.0);
  VertOut.texCoord = vertex;
}
