#version 440

layout (binding = 0) uniform positionBuffer
{
	vec3 origin;
};

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 direction;
layout(location = 2) in float velocity;
layout(location = 3) in float life;

out VertexData
{
	vec3 position;
	vec3 direction;
	float velocity;
	float life;
} VertOut;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(void)
{
	if(life < 100)
	{
		VertOut.position = position + vec3(normalize(direction) * velocity);
		if(life < 20)
			VertOut.direction = direction;
		else
			VertOut.direction = normalize(direction + vec3(0, -0.01, 0));
		VertOut.velocity = velocity;
		VertOut.life = life + 0.5;
	}
	else
	{
		VertOut.position = position;
		VertOut.direction = direction;
		VertOut.velocity = velocity;
		VertOut.life = life;
	}
}
