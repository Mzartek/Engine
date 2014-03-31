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

void main(void)
{
	vec4 final_color;
	vec3 L, N, D, E, R;
	float cos_cur_angle, cos_inner_cone_angle, cos_outer_cone_angle, cos_inner_minus_outer_angle, lambertTerm, spot, specular;

	final_color = outLight.ambient * outMat.ambient;

	L = normalize(lightDir);
	N = normalize(normal);
	
	lambertTerm = dot(L,N);
	if(lambertTerm > 0.0)
	{
		D = normalize(outLight.spotDirection);
		E = normalize(eyeVec);
		R = reflect(-L, N);
		
		cos_cur_angle = dot(-L, D);
	      	cos_inner_cone_angle = cos(radians(outLight.spotCutOff));
	      	cos_outer_cone_angle = cos_inner_cone_angle - 0.1;
	      	cos_inner_minus_outer_angle = cos_inner_cone_angle - cos_outer_cone_angle;
		spot = clamp((cos_cur_angle - cos_outer_cone_angle) / cos_inner_minus_outer_angle, 0.0, 1.0);

		specular = pow(max(dot(R, E), 0.0), outMat.shininess);
		
		final_color += outLight.diffuse * outMat.diffuse * lambertTerm * spot;
		final_color += outLight.specular * outMat.specular * specular * spot;
	}

	fragColor = texture(colorTexture, outTexCoord) * final_color;
}