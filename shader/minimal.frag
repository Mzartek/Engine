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

const float cos_outer_cone_angle = 0.7;

void main(void)
{
	vec4 final_color = outLight.ambient * outMat.ambient;

	vec3 L = normalize(lightDir);
	vec3 D = normalize(outLight.spotDirection);

	float cos_cur_angle = dot(-L, D);

	float cos_inner_cone_angle = cos(radians(outLight.spotCutOff));

	float cos_inner_minus_outer_angle = cos_inner_cone_angle - cos_outer_cone_angle;
	
	float spot = 0.0;
	spot = clamp((cos_cur_angle - cos_outer_cone_angle) / cos_inner_minus_outer_angle, 0.0, 1.0);

	vec3 N = normalize(normal);

	float lambertTerm = max(dot(N,L), 0.0);
	if(lambertTerm > 0.0)
	{
		final_color += outLight.diffuse * outMat.diffuse * lambertTerm * spot;

		vec3 E = normalize(eyeVec);
		vec3 R = reflect(-L, N);

		float specular = pow(max(dot(R, E), 0.0), outMat.shininess);

		final_color += outLight.specular * outMat.specular * specular * spot;
	}

	fragColor = texture(colorTexture, outTexCoord) * final_color;
}