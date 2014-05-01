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
  vec3 rayDir;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  vec4 shadowCoord;
};

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

// Texture
uniform sampler2D colorTexture;
uniform sampler2DShadow dirShadowMap;
uniform sampler2DShadow spotShadowMap;

// In
in vec2 outTexCoord;
in material outMat;
in dirLight outDirLight;
in spotLight outSpotLight;
in vec3 normal, eyeVec;

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
      
      final_color += light.diffuse * outMat.diffuse * cosTheta * shadow * vec4(2.0, 2.0, 2.0, 1.0);
      final_color += light.specular * outMat.specular * specular * shadow;
    }
  
  return final_color;
}

void main(void)
{
  vec4 final_color;
  vec3 N = normalize(normal);
  float shadow;

  shadow = calcShadow(dirShadowMap, outDirLight.shadowCoord);
  final_color = calcDirLight(outDirLight, N, shadow);
  
  /* shadow = calcShadow(spotShadowMap, outSpotLight.shadowCoord); */
  /* final_color = calcSpotLight(outSpotLight, N, shadow); */
  
  fragColor = texture(colorTexture, outTexCoord) * final_color;
}

/* vec4 calcSpotLight(spotLight light, vec3 N, float shadow) */
/* { */
/*   vec4 final_color; */
/*   vec3 L, D, E, R; */
/*   float cos_cur_angle, cos_inner_cone_angle, cos_outer_cone_angle, cos_inner_minus_outer_angle; */
/*   float cosTheta, spot, specular; */

/*   final_color = light.ambient * outMat.ambient; */
  
/*   L = normalize(light.rayDir); */
  
/*   cosTheta = dot(L,N); */
/*   if(cosTheta > 0.0) */
/*     { */
/*       D = normalize(light.spotDirection); */
/*       E = normalize(eyeVec); */
/*       R = reflect(-L, N); */
		
/*       cos_cur_angle = dot(-L, D); */
/*       cos_outer_cone_angle = cos(radians(light.spotCutOff)); */
/*       cos_inner_cone_angle = cos_outer_cone_angle + 0.1; */
/*       cos_inner_minus_outer_angle = cos_inner_cone_angle - cos_outer_cone_angle; */
/*       spot = clamp((cos_cur_angle - cos_outer_cone_angle) / cos_inner_minus_outer_angle, 0.0, 1.0); */

/*       specular = pow(max(dot(R, E), 0.0), outMat.shininess); */
      
/*       final_color += light.diffuse * outMat.diffuse * spot * shadow; */
/*       final_color += light.specular * outMat.specular * specular * spot * shadow; */
/*     } */

/*   return final_color; */
/* } */
