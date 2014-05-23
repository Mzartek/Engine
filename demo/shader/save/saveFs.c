struct spotLight
{
  vec3 spotDirection;
  float spotCutOff;
  vec3 rayDir;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  vec4 shadowCoord;
};

uniform sampler2DShadow spotShadowMap;

in spotLight outSpotLight;

vec4 calcSpotLight(spotLight light, vec3 N, float shadow)
{
	vec4 final_color;
	vec3 L, D, E, R;
	float cos_cur_angle, cos_inner_cone_angle, cos_outer_cone_angle, cos_inner_minus_outer_angle;
	float cosTheta, spot, specular;

	final_color = light.ambient * outMat.ambient;
  
	L = normalize(light.rayDir);
  
	cosTheta = dot(L,N);
	if(cosTheta > 0.0)
	{
		D = normalize(light.spotDirection);
		E = normalize(eyeVec);
		R = reflect(-L, N);
		
		cos_cur_angle = dot(-L, D);
		cos_outer_cone_angle = cos(radians(light.spotCutOff));
		cos_inner_cone_angle = cos_outer_cone_angle + 0.1;
		cos_inner_minus_outer_angle = cos_inner_cone_angle - cos_outer_cone_angle;
		spot = clamp((cos_cur_angle - cos_outer_cone_angle) / cos_inner_minus_outer_angle, 0.0, 1.0);

		specular = pow(max(dot(R, E), 0.0), outMat.shininess);
      
		final_color += light.diffuse * outMat.diffuse * spot * shadow;
		final_color += light.specular * outMat.specular * specular * spot * shadow;
	}

	return final_color;
}

void main(void)
{
	shadow = calcShadow(spotShadowMap, outSpotLight.shadowCoord);
	final_color = calcSpotLight(outSpotLight, N, shadow);
}
