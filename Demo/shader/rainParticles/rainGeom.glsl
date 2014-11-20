#version 440

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in VertexData
{
	vec4 particle;
} GeomIn[];

out VertexData
{
	vec2 texCoord;
} GeomOut;

void main(void)
{
	vec4 particle = GeomIn[0].particle;

	gl_Position = vec4(particle.x - 1, particle.y - 1, particle.zw);
	GeomOut.texCoord = vec2(0, 0);
	EmitVertex();

	gl_Position = vec4(particle.x + 1, particle.y - 1, particle.zw);
	GeomOut.texCoord = vec2(1, 0);
	EmitVertex();

	gl_Position = vec4(particle.x - 1, particle.y + 1, particle.zw);
	GeomOut.texCoord = vec2(0, 1);
	EmitVertex();

	gl_Position = vec4(particle.x + 1, particle.y + 1, particle.zw);
	GeomOut.texCoord = vec2(1, 1);
	EmitVertex();

	EndPrimitive();
}