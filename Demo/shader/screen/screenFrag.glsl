#version 440

uniform sampler2D backgroundTexture;

layout(binding = 0) uniform colorBuffer
{
	vec4 color;
};

layout(location = 0) out vec4 fragColor;

void main(void)
{
	fragColor = texelFetch(backgroundTexture, ivec2(gl_FragCoord.xy), 0) * color;
}
