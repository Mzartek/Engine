uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec4 matAmbiant;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

in vec4 vertexArray;
in vec2 textureArray;
in vec4 normalArray;

varying out vec4 color;
varying out vec2 texCoord;

void main(void)
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertexArray;
	texCoord = textureArray;
	color = matDiffuse;
}