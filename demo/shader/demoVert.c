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
uniform vec3 dirLightDirection;
uniform vec4 dirLightAmbient, dirLightDiffuse, dirLightSpecular;
uniform mat4 dirShadowMVP;

//Attribute
layout(location = 0) in vec3 vertexArray;
layout(location = 1) in vec2 textureArray;
layout(location = 2) in vec3 normalArray;

//Out
out vec2 outTexCoord;
out material outMat;
out dirLight outDirLight;
out vec3 normal, eyeVec;

void materialInit(void)
{
  outMat.ambient = matAmbient;
  outMat.diffuse = matDiffuse;
  outMat.specular = matSpecular;
  outMat.shininess = matShininess;
}

void dirLightInit(void)
{
  outDirLight.rayDir = dirLightDirection;
  outDirLight.ambient = dirLightAmbient;
  outDirLight.diffuse = dirLightDiffuse;
  outDirLight.specular = dirLightSpecular;
  outDirLight.shadowCoord = dirShadowMVP * vec4(vertexArray, 1.0);
}

void main(void)
{
  vec3 vVertex = vec3(modelMatrix * vec4(vertexArray, 1.0));
  
  gl_Position = MVP * vec4(vertexArray, 1.0);
  outTexCoord = vec2(textureArray.x, 1.0 - textureArray.y);
  
  normal = normalMatrix * normalArray;
  eyeVec = camPosition - vVertex;

  materialInit();

  dirLightInit();
}
