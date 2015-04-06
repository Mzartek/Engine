#version 440

layout (points) in;
layout (points, max_vertices = 1) out;

in VertexData
{
	vec3 position;
	vec3 direction;
	float velocity;
	float life;
} GeomIn[];

out vec3 outPosition;
out vec3 outDirection;
out float outVelocity;
out float outLife;

void main(void)
{
	outPosition = GeomIn[0].position;
	outDirection = GeomIn[0].direction;
	outVelocity = GeomIn[0].velocity;
	outLife = GeomIn[0].life;

	EmitVertex();
	EndPrimitive();
}