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
  vec3 spotDirection;
  float spotCutOff;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
};

//Matrix
uniform mat4 projectionMatrix, viewMatrix, modelMatrix;

//Material
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;

//Light
uniform vec3 camPosition, lightPosition, lightSpotDirection;
uniform float lightSpotCutOff;
uniform vec4 lightAmbient, lightDiffuse, lightSpecular;

//Attribute
layout(location = 0) in vec3 vertexArray;
layout(location = 1) in vec2 textureArray;
layout(location = 2) in vec3 normalArray;

//Out
out vec2 outTexCoord;
out material outMat;
out light outLight;
out vec3 normal, lightDir, eyeVec;

void materialInit(void)
{
  outMat.ambient = matAmbient;
  outMat.diffuse = matDiffuse;
  outMat.specular = matSpecular;
  outMat.shininess = matShininess;
}

void lightInit(void)
{
  mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
  vec3 vVertex = vec3(modelMatrix * vec4(vertexArray, 1.0));

  outLight.spotDirection = lightSpotDirection;
  outLight.spotCutOff = lightSpotCutOff;
  outLight.ambient = lightAmbient;
  outLight.diffuse = lightDiffuse;
  outLight.specular = lightSpecular;
	
  normal = vec3(normalMatrix * normalArray);
  lightDir = lightPosition - vVertex;
  eyeVec = camPosition - vVertex;
}

void main(void)
{	
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexArray, 1.0);

  outTexCoord = vec2(textureArray.x, 1 - textureArray.y);

  materialInit();

  lightInit();
}
