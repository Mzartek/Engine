//Matrix
uniform mat4 projectionMatrix, viewMatrix, modelMatrix;

//Material
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;

//Light
uniform vec3 lightPosition, spotDirection;
uniform float spotCone;
uniform vec4 lightAmbient, lightDiffuse, lightSpecular;

//Attribute
in vec3 vertexArray, normalArray;
in vec2 textureArray;

//Out
varying out vec2 outTexCoord;

varying out vec4 outMatAmbient, outMatDiffuse, outMatSpecular;
varying out float outMatShininess;

varying out vec4 outLightAmbient, outLightDiffuse, outLightSpecular;
varying out vec3 outNormal, outLightDir, outEyeVec;

void lightInit(void)
{
	vec3 vVertex;
	mat4 normalMatrix = transpose(inverse(modelMatrix));

	outLightAmbient = lightAmbient;
	outLightDiffuse = lightDiffuse;
	outLightSpecular = lightSpecular;

	vVertex = vec3(modelMatrix * vec4(vertexArray.x, vertexArray.y, vertexArray.z, 1.0));
	outNormal = vec3(normalMatrix * vec4(normalArray.x, normalArray.y, normalArray.z, 1.0));
	outLightDir = lightPosition - vVertex;
	outEyeVec = -vVertex;
}

void main(void)
{
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexArray.x, vertexArray.y, vertexArray.z, 1.0);

	outTexCoord = vec2(textureArray.x, 1 - textureArray.y);
	
	outMatAmbient = matAmbient;
	outMatDiffuse = matDiffuse;
	outMatSpecular = matSpecular;
	outMatShininess = matShininess;

	lightInit();
}