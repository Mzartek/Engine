#version 330

uniform vec4 color;
uniform usampler2D materialTexture;

uniform uvec2 screen;

out vec4 fragColor;

vec2 screenTexCoord = vec2(gl_FragCoord.x/screen.x, gl_FragCoord.y/screen.y);

void main(void)
{
	uvec4 material = texture(materialTexture, screenTexCoord);	
	
	fragColor = vec4(0x000000FF & (ivec4(material) >> 24)) / 255;
	fragColor *= color;
}
