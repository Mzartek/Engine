#version 330

uniform sampler2D textTex;

in vec2 outTexCoord;

out vec4 fragColor;

void main(void)
{
	fragColor = texture(textTex, outTexCoord);
}
