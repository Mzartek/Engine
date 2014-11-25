#version 440

layout(location = 0) in vec3 particle;
layout(location = 1) in float life;

out VertexData
{
	vec4 particle;
} VertOut;

void main(void)
{
    float test = (100 - life) * 100 / 100;
    vec4 direction = vec4(0, -test, 0, 0);
	VertOut.particle = vec4(particle.x, particle.y, particle.z, 1.0) + direction;
}
