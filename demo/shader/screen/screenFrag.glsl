#version 330

uniform usampler2D materialTexture;

uniform vec4 color;

out vec4 fragColor;

ivec4 unpack(uvec4 a, int v)
{
	return (0x000000FF & (ivec4(a) >> (v * 8)));
}

void main(void)
{
	uvec4 material = texelFetch(materialTexture, ivec2(gl_FragCoord.xy), 0);
	
	fragColor = vec4(unpack(material, 3)) / 255;
	fragColor *= color;
}
