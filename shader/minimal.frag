uniform sampler2D colorTexture;

in vec4 outMatAmbient, outMatDiffuse, outMatSpecular;
in float outMatShininess;

in vec4 outLightAmbient, outLightDiffuse, outLightSpecular;
in vec3 outNormal, outLightDir, outEyeVec;

in vec2 outTexCoord;

//Final out
varying out vec4 fragColor;

void main(void)
{
	vec4 sceneColor = vec4(0, 0, 0, 0.0) + outMatAmbient * outLightAmbient;
	vec4 finalColor = (sceneColor * outMatAmbient) + (outLightAmbient * outMatAmbient);
							
	vec3 N = normalize(outNormal);
	vec3 L = normalize(outLightDir);
	
	float lambertTerm = dot(N,L);
	
	if(lambertTerm > 0.0)
	{
		finalColor += outLightDiffuse * outMatDiffuse * lambertTerm;	
		
		vec3 E = normalize(outEyeVec);
		vec3 R = reflect(-L, N);
		float specular = pow(max(dot(R, E), 0.0), outMatShininess);
		finalColor += outLightSpecular * outMatSpecular * specular;	
	}
	
	fragColor = texture(colorTexture, outTexCoord) * finalColor;
}