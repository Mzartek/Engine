#version 330

uniform vec4 color;
uniform usampler2D materialTexture;

out vec4 fragColor;

void main(void)
{
	uvec4 material = texelFetch(materialTexture, ivec2(gl_FragCoord.xy), 0);
	
	fragColor = vec4(0x000000FF & (ivec4(material) >> 24)) / 255;
	fragColor *= color;
}
