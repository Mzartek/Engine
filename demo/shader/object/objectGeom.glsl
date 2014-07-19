#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec2 vtexCoord[];
in vec3 vnormal[];

out vec2 texCoord;
out vec3 normal;

out VertexData
{
	vec2 texCoord;
	vec3 normal;
} VertexOut;

void main(void)
{
	int i;
	for(i = 0; i<gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		texCoord = vtexCoord[i];
		normal = vnormal[i];

		EmitVertex();
	}
}