#version 330

uniform sampler2D colorTexture;
uniform sampler2D shadowMap;

in vec2 texCoord;

void main()
{
	float transparency = texture(colorTexture, texCoord).a;
	if (transparency > 0.5)
		gl_FragDepth = gl_FragCoord.z;
	else
		gl_FragDepth = texelFetch(shadowMap, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0).z;
}
