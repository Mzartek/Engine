#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec2 vtexCoord[];
in vec3 vnormal[];

in VertexData
{
	vec2 texCoord;
	vec3 normal;
} GeomIn[];

out VertexData
{
	vec2 texCoord;
	vec3 normal;
} GeomOut;

void main(void)
{
	int i;
	for(i = 0; i<gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		GeomOut.texCoord = GeomIn[i].texCoord;
		GeomOut.normal = GeomIn[i].normal;

		EmitVertex();
	}
}