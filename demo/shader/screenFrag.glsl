#version 330

uniform vec4 color;
uniform usampler2D materialTexture;
uniform usampler2D lightTexture;

out vec4 fragColor;

void main(void)
{
	uvec4 material = texelFetch(materialTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0);
	uvec4 light = texelFetch(lightTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0);

	vec4 matAmbient = vec4(0x000000FF & (ivec4(material) >> 24)) / 255;
	vec4 matDiffuse = vec4(0x000000FF & (ivec4(material) >> 16)) / 255;
	vec4 matSpecular = vec4(0x000000FF & (ivec4(material) >> 8)) / 255;
	vec4 lightDiffuse = vec4(0x0000FFFF & (ivec4(light) >> 16)) / 65535;
	vec4 lightSpecular = vec4(0x0000FFFF & ivec4(light)) / 65535;

	fragColor = matAmbient + (matDiffuse * lightDiffuse) + (matSpecular * lightSpecular);
}
