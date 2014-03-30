//version 330

struct material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

struct light
{
	vec3 position;
	vec3 spotDirection;
	float spotCutOff;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

//Matrix
uniform mat4 projectionMatrix, viewMatrix, modelMatrix;

//Attribute
in vec3 vertexArray, normalArray;
in vec2 textureArray;

//Material
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;

//Light
uniform vec3 lightPosition, lightSpotDirection;
uniform float lightSpotCutOff;
uniform vec4 lightAmbient, lightDiffuse, lightSpecular;

//Out
varying out vec2 outTexCoord;
varying out material outMat;
varying out light outLight;
varying out vec3 normal, lightDir, eyeVec;

void materialInit(void)
{
	outMat.ambient = matAmbient;
	outMat.diffuse = matDiffuse;
	outMat.specular = matSpecular;
	outMat.shininess = matShininess;
}

void lightInit(void)
{
	mat3 normalMatrix = transpose(inverse(modelMatrix));

	outLight.position = lightPosition;
	outLight.spotDirection = lightSpotDirection;
	outLight.spotCutOff = lightSpotCutOff;
	outLight.ambient = lightAmbient;
	outLight.diffuse = lightDiffuse;
	outLight.specular = lightSpecular;
	
	vec3 vVertex = vec3(modelMatrix * vec4(vertexArray, 1.0));
	normal = vec3(normalMatrix * normalArray);
	lightDir = vec3(lightPosition - vVertex);
	eyeVec = -vVertex;
}

void main(void)
{
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexArray, 1.0);

	outTexCoord = vec2(textureArray.x, 1 - textureArray.y);

	materialInit();

	lightInit();
}