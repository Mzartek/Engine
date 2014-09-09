#version 330

uniform sampler2D backgroundTexture;

uniform vec4 color;

out vec4 fragColor;

void main(void)
{
	fragColor = texelFetch(backgroundTexture, ivec2(gl_FragCoord.xy), 0) * color;
}
