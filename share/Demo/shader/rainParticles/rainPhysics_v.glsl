#version 440

uniform sampler2DShadow depthMap;

layout (binding = 0) uniform positionBuffer
{
	vec3 origin;
};

layout (binding = 1) uniform depthBuffer
{
	mat4 depthMatrix;
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

float check_position(vec4 coord)
{
	coord.x = 0.5f + (coord.x / coord.w * 0.5f);
	coord.y = 0.5f + (coord.y / coord.w * 0.5f);
	coord.z = 0.5f + (coord.z / coord.w * 0.5f);
	
	return texture (depthMap, coord.xyz);
}

void main(void)
{	
	if(life < 100)
	{
		vec3 nextPosition = position + vec3(normalize(direction) * velocity);
		
		/*if (check_position (depthMatrix * vec4(nextPosition, 1.0)) < 1.0f) 
			VertOut.position = position;
		else*/ 
		VertOut.position = nextPosition;
		
		VertOut.direction = direction;
		VertOut.velocity = velocity;
		VertOut.life = life + 1.0;
	}
	else
	{
		float num0 = (rand(position.xz) * 200) - 100;
		float num1 = (rand(position.zx) * 200) - 100;
		float num2 = (rand(direction.xz) * 2) - 1;
		float num3 = (rand(direction.zx) * 2) - 1;

		VertOut.position = vec3(origin.x + num0, origin.y + 100, origin.z + num1);
		VertOut.direction = normalize(vec3(num2, -2, num3));
		VertOut.velocity = velocity;
		VertOut.life = rand(vec2(num0, num1));
	}
}
