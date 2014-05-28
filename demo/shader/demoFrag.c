#version 330

struct material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

// Texture
uniform sampler2D colorTexture;
uniform sampler2D lightDiffuseTexture;
uniform sampler2D lightSpecularTexture;

// In
in float outScreenWidth, outScreenHeight;
in vec2 outTexCoord;
in material outMat;

out vec4 fragColor;

void main(void)
{
	vec2 lightCoord = vec2(gl_FragCoord.x/outScreenWidth, gl_FragCoord.y/outScreenHeight);
	vec4 final_color, lightDiff, lightSpec;

	if(lightCoord.x >= 0.0 && lightCoord.x <= 1.0 && lightCoord.y >= 0.0 && lightCoord.y <= 1.0)
	{
		lightDiff = texture(lightDiffuseTexture, lightCoord);
		lightSpec = texture(lightSpecularTexture, lightCoord);
		final_color = outMat.ambient + (outMat.diffuse * lightDiff) + (outMat.specular * lightSpec);
		fragColor = texture(colorTexture, outTexCoord) * final_color;
	}
}
