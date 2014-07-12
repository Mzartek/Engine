#version 330

// Texture
uniform sampler2D colorTexture;
uniform usampler2D lightTexture;

uniform float screenWidth, screenHeight;
uniform vec4 matAmbient, matDiffuse, matSpecular;

// In
in vec2 outTexCoord;

out vec4 fragColor;

void main(void)
{
	ivec2 lightCoord = ivec2(gl_FragCoord.x, gl_FragCoord.y);
	uvec4 srcLight = texelFetch(lightTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0);
	vec4 lightDiff = vec4(0x0000FFFF & (ivec4(srcLight) >> 16)) / 65535;
	vec4 lightSpec = vec4(0x0000FFFF & ivec4(srcLight)) / 65535;
	vec4 final_color = matAmbient + (matDiffuse * lightDiff) + (matSpecular * lightSpec);

	fragColor = texture(colorTexture, outTexCoord) * final_color;
}
