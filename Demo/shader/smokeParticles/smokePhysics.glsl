#version 440

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 direction;
layout(location = 2) in float velocity;
layout(location = 3) in float life;

out vec3 outPosition;
out vec3 outDirection;
out float outVelocity;
out float outLife;

/*int rand(int seed)
{
    int res = ((1103515245 * seed) + 0) & 0x7FFFFFFF;
    return res;
}*/

void main(void)
{
	if(life < 100)
	{
		outPosition = position;
		outDirection = direction;
		outVelocity = velocity;
		outLife = life + 1;
	}
	else
	{
		outPosition = vec3(0, 0, 0);
		outDirection = direction;
		outVelocity = velocity;
		outLife = 0;
	}
}
