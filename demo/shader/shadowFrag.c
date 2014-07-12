#version 330

uniform sampler2D colorTexture;
uniform sampler2D shadowMap;
uniform float alpha;
uniform vec2 screen;

in vec2 texCoord;

void main()
{
	float transparency = texture(colorTexture, texCoord).a * alpha;
	if (transparency > 0.5)
		gl_FragDepth = gl_FragCoord.z;
	else
		gl_FragDepth = texture(shadowMap, vec2(gl_FragCoord.x/screen.x, gl_FragCoord.y/screen.y)).z;
}
