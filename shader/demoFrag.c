#version 330

struct material
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};

struct light
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
};

// Texture
uniform sampler2D colorTexture;
uniform sampler2DShadow shadowMap;

// In
in vec2 outTexCoord;
in vec4 outShadowCoord;
in material outMat;
in light outLight;
in vec3 normal, rayDir, eyeVec;

//Final out
out vec4 fragColor;

void main(void)
{
  vec4 final_color;
  vec3 L, N, E, R;
  float x, y;
  float cosTheta, spot, specular;

  final_color = outLight.ambient * outMat.ambient;
  if(textureProj(shadowMap, outShadowCoord) >= outShadowCoord.z-0.005)
    {
      L = normalize(rayDir);
      N = normalize(normal);
	
      cosTheta = dot(-L,N);
      if(cosTheta > 0.0)
	{
	  E = normalize(eyeVec);
	  R = reflect(L, N);

	  specular = pow(max(dot(R, E), 0.0), outMat.shininess);
      
	  final_color += outLight.diffuse * outMat.diffuse * cosTheta;
	  final_color += outLight.specular * outMat.specular * specular;
	}
    }
  
  fragColor = texture(colorTexture, outTexCoord) * final_color;
}
