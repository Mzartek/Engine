#version 330

uniform vec4 color;
uniform usampler2D materialTexture;

out vec3 fragColor;

void main(void)
{
	uvec3 material = texelFetch(materialTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0).xyz;
	vec3 finalColor = vec3(0x000000FF & (ivec3(material) >> 24)) / 255;

	fragColor = finalColor;
}
