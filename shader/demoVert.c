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

//Matrix
uniform mat4 MVP, modelMatrix;
uniform mat3 normalMatrix;

//Material
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;

//Camera
uniform vec3 camPosition;

//dirLight 0
uniform vec3 dirLightDirection0;
uniform vec4 dirLightAmbient0, dirLightDiffuse0, dirLightSpecular0;
uniform mat4 dirShadowMVP0;

//spotLight 0
uniform vec3 spotLightPosition0, spotLightDirection0;
uniform float spotLightCutOff0;
uniform vec4 spotLightAmbient0, spotLightDiffuse0, spotLightSpecular0;
uniform mat4 spotShadowMVP0;

//Attribute
layout(location = 0) in vec3 vertexArray;
layout(location = 1) in vec2 textureArray;
layout(location = 2) in vec3 normalArray;

//Out
out vec2 outTexCoord;
out material outMat;
out dirLight outDirLight0;
out vec3 normal, eyeVec;

void materialInit(void)
{
  outMat.ambient = matAmbient;
  outMat.diffuse = matDiffuse;
  outMat.specular = matSpecular;
  outMat.shininess = matShininess;
}

void dirLight0Init(void)
{
  outDirLight0.rayDir = dirLightDirection0;
  outDirLight0.ambient = dirLightAmbient0;
  outDirLight0.diffuse = dirLightDiffuse0;
  outDirLight0.specular = dirLightSpecular0;
  outDirLight0.shadowCoord = dirShadowMVP0 * vec4(vertexArray, 1.0);
}

void main(void)
{
  vec3 vVertex = vec3(modelMatrix * vec4(vertexArray, 1.0));
  
  gl_Position =  MVP * vec4(vertexArray, 1.0);
  outTexCoord = vec2(textureArray.x, 1.0 - textureArray.y);
  
  normal = vec3(normalMatrix * normalArray);
  eyeVec = camPosition - vVertex;

  materialInit();

  dirLight0Init();
}
