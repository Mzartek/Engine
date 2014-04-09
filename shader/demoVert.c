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

//Matrix
uniform mat4 biasMatrix;
uniform mat4 projectionMatrix, viewMatrix, modelMatrix;
uniform mat4 depthProjectionMatrix, depthViewMatrix;

//Material
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;

//Camera
uniform vec3 camPosition;

//Spot Light
uniform vec3 lightDirection;
uniform vec4 lightAmbient, lightDiffuse, lightSpecular;

//Attribute
layout(location = 0) in vec3 vertexArray;
layout(location = 1) in vec2 textureArray;
layout(location = 2) in vec3 normalArray;

//Out
out vec2 outTexCoord;
out vec4 outShadowCoord;
out material outMat;
out light outLight;
out vec3 normal, rayDir, eyeVec;

void materialInit(void)
{
  outMat.ambient = matAmbient;
  outMat.diffuse = matDiffuse;
  outMat.specular = matSpecular;
  outMat.shininess = matShininess;
}

void lightInit(void)
{
  outLight.ambient = lightAmbient;
  outLight.diffuse = lightDiffuse;
  outLight.specular = lightSpecular;
}

void main(void)
{
  mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
  vec3 vVertex = vec3(modelMatrix * vec4(vertexArray, 1.0));
  mat4 depthBiasMVP = biasMatrix * depthProjectionMatrix * depthViewMatrix * modelMatrix;
  
  normal = vec3(normalMatrix * normalArray);
  rayDir = lightDirection;
  eyeVec = camPosition - vVertex;
  
  gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vec4(vertexArray, 1.0);

  outTexCoord = vec2(textureArray.x, 1.0 - textureArray.y);
  outShadowCoord = depthBiasMVP * vec4(vertexArray, 1.0);

  materialInit();

  lightInit();
}
