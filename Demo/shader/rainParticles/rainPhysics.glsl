#version 440

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 direction;
layout(location = 2) in float life;

out vec3 outPosition;
out vec3 outDirection;
out float outLife;

void main(void)
{
	if(life <= 0)
	{
		outPosition = vec3(position.x, 50, position.z);
		outDirection = vec3(0.5, -1, 0);
		outLife = 100;
	}
	else
	{
		outPosition = position;
		outDirection = direction;
		outLife = life - 1;
	}
}