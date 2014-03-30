//version 330

struct material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

struct light
{
	vec3 position;
	vec3 spotDirection;
	float spotCutOff;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

uniform sampler2D colorTexture;

in vec2 outTexCoord;
in material outMat;
in light outLight;
in vec3 normal, lightDir, eyeVec;

//Final out
varying out vec4 fragColor;

void main(void)
{
	vec4 final_color = outLight.ambient * outMat.ambient;
							
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	
	float lambertTerm = dot(N,L);
	
	if(lambertTerm > 0.0)
	{
		final_color += outLight.diffuse * outMat.diffuse * lambertTerm;

		vec3 E = normalize(eyeVec);
		vec3 R = reflect(-L, N);
		
		float specular = pow(max(dot(R, E), 0.0), outMat.shininess);
				 
		final_color += outLight.specular * outMat.specular * specular;	
	}

	fragColor = texture(colorTexture, outTexCoord) * final_color;
}