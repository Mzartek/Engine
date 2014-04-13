#version 330

struct material
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};

struct dirLight
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  vec3 rayDir;
};

// Texture
uniform sampler2D colorTexture;
uniform sampler2DShadow dirShadowMap;

// In
in vec2 outTexCoord;
in material outMat;
in dirLight outDirLight;
in vec4 outDirShadowCoord;
in vec3 normal, eyeVec;

//Final out
out vec4 fragColor;

float lookUp(sampler2DShadow tex, vec4 coord, vec2 offSet, ivec2 texSize)
{
  return textureProj(tex, vec4(coord.x + (offSet.x * (1.0/texSize.x)), coord.y + (offSet.y * (1.0/texSize.y)), coord.z-0.005, coord.w));
}

float calcShadow(sampler2DShadow tex, vec4 coord)
{
  ivec2 texSize = textureSize(tex, 0);
  float x, y, shadow = 0.0;
  
  for(x=-1.0 ; x<=1.0 ; x+=1.0)
    for(y=-1.0 ; y<=1.0 ; y+=1.0)
      shadow += lookUp(tex, coord, vec2(x,y), texSize);
  shadow /= 9.0;

  return shadow;
}

vec4 calcDirLight(dirLight light, vec3 N, float shadow) // N need to be normalize
{
  vec4 final_color;
  vec3 L, E, R;
  float cosTheta, spot, specular;

  final_color = light.ambient * outMat.ambient;
  
  L = normalize(light.rayDir);
	
  cosTheta = dot(-L,N);
  if(cosTheta > 0.0)
    {
      E = normalize(eyeVec);
      R = reflect(L, N);

      specular = pow(max(dot(R, E), 0.0), outMat.shininess);
      
      final_color += light.diffuse * outMat.diffuse * cosTheta * shadow;
      final_color += light.specular * outMat.specular * specular * shadow;
    }
  
  return final_color;
}

void main(void)
{
  vec4 final_color;
  vec3 N = normalize(normal);
  float shadow;

  shadow = calcShadow(dirShadowMap, outDirShadowCoord);
  final_color = calcDirLight(outDirLight, N, shadow);
  
  fragColor = texture(colorTexture, outTexCoord) * final_color;
}
