#version 440

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 direction;
layout(location = 2) in float life;

out vec3 outPosition;
out vec3 outDirection;
out float outLife;

void main(void)
{
	outPosition = position;
	outDirection = direction;
	outLife = life - 1;
}