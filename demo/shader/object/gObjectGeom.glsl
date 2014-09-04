#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VertexData
{
	vec2 texCoord;
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
} GeomIn[];

out VertexData
{
	vec2 texCoord;
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
} GeomOut;

void main(void)
{
	int i;
	for(i = 0; i<3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		GeomOut.texCoord = GeomIn[i].texCoord;
		GeomOut.normal = GeomIn[i].normal;
		GeomOut.tangent = GeomIn[i].tangent;
		GeomOut.bitangent = GeomIn[i].bitangent;

		EmitVertex();
	}
	EndPrimitive();
}