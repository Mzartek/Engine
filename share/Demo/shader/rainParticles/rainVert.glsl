#version 440

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 direction;
layout(location = 2) in float velocity;
layout(location = 3) in float life;

out VertexData
{
     vec4 particle;
} VertOut;

void main(void)
{
     VertOut.particle = vec4(position.xyz, 1.0) + vec4(normalize(direction) * life * velocity, 1.0);
}
