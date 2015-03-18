#version 440

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 direction;
layout(location = 2) in float velocity;
layout(location = 3) in float life;

out vec3 outPosition;
out vec3 outDirection;
out float outVelocity;
out float outLife;

layout (binding = 0) uniform positionBuffer
{
	vec3 origin;
};

layout (binding = 1) uniform cameraBuffer
{
    vec3 camPosition;
    vec3 camTarget;
};

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(void)
{
	if(life < 100)
	{
		outPosition = position + vec3(normalize(direction) * velocity);
		outDirection = direction;
		outVelocity = velocity;
		outLife = life + 1.0;
	}
	else
	{
		float num0 = rand(direction.xz);

		outPosition = origin;
		outDirection = normalize(vec3(num0, 0.50, 0));
		outVelocity = velocity;
		outLife = 0;
	}
}
