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
		VertOut.direction = direction;
		VertOut.velocity = velocity;
		VertOut.life = life + 1.0;
	}
	else
	{
		float num0 = (rand(direction.xz) * 2) - 1;
		float num1 = (rand(direction.zx) * 2) - 1;

		VertOut.position = origin;
		VertOut.direction = normalize(vec3(num0, 1.0f, num1));
		VertOut.velocity = velocity;
		VertOut.life = rand(vec2(num0, num1));
	}
}
