#version 330

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

uniform vec3 spotLightPosition, spotLightDirection;
uniform float spotLightCutOff;
uniform vec4 spotLightAmbient, spotLightDiffuse, spotLightSpecular;
uniform mat4 spotShadowMVP;

out spotLight outSpotLight;

void spotLightInit(vec3 vVertex)
{
  outSpotLight.spotDirection = spotLightDirection;
  outSpotLight.spotCutOff = spotLightCutOff;
  outSpotLight.rayDir = spotLightPosition - vVertex;
  outSpotLight.ambient = spotLightAmbient;
  outSpotLight.diffuse = spotLightDiffuse;
  outSpotLight.specular = spotLightSpecular;
  outSpotLight.shadowCoord = spotShadowMVP * vec4(vertexArray, 1.0);
}
