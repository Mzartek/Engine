#version 440

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 direction;
layout(location = 2) in float velocity;
layout(location = 3) in float life;

out VertexData
{
     vec4 particle;
     vec3 color;
     float life;
} VertOut;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(void)
{
     VertOut.particle = vec4(position.xyz, 1.0);// + vec4(normalize(direction) * life * velocity, 1.0);
     VertOut.color = vec3(
	  rand(vec2(position.x, position.y)),
	  rand(vec2(position.y, position.z)),
	  rand(vec2(position.x, position.z)));
     VertOut.life = life;
}
