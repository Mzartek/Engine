#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VertexData
{
	vec2 texCoord;
	mat3 TBN;
} GeomIn[];

out VertexData
{
	vec2 texCoord;
	mat3 TBN;
} GeomOut;

void main(void)
{
	int i;
	for(i = 0; i<3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		GeomOut.texCoord = GeomIn[i].texCoord;
		GeomOut.TBN = GeomIn[i].TBN;

		EmitVertex();
	}
	EndPrimitive();
}