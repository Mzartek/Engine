#version 330

// Texture
uniform sampler2D colorTexture;
uniform sampler2D lightDiffuseTexture;
uniform sampler2D lightSpecularTexture;

uniform float screenWidth, screenHeight;
uniform vec4 matAmbient, matDiffuse, matSpecular;

// In
in vec2 outTexCoord;

out vec4 fragColor;

void main(void)
{
	vec2 lightCoord = vec2(gl_FragCoord.x/screenWidth, gl_FragCoord.y/screenHeight);
	vec4 lightDiff = texture(lightDiffuseTexture, lightCoord);
	vec4 lightSpec = texture(lightSpecularTexture, lightCoord);
	vec4 final_color;

	final_color = matAmbient + (matDiffuse * lightDiff) + (matSpecular * lightSpec);
	fragColor = texture(colorTexture, outTexCoord) * final_color;
}
