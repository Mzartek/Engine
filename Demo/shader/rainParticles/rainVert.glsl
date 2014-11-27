#version 440

layout(location = 0) in vec3 particle;
layout(location = 1) in vec3 direction;
layout(location = 2) in float life;

out VertexData
{
     vec4 particle;
} VertOut;

void main(void)
{
     float test = (100 - life) * 100 / 100;
     VertOut.particle = vec4(particle.x, particle.y, particle.z, 1.0) + vec4(normalize(direction) * test, 1.0);
}
