attribute vec4 vertexArray;
attribute vec4 textureArray;
attribute vec4 normalArray;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform vec4 matAmbiant;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

void main(void)
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertexArray;
	gl_TexCoord[0] = textureArray;
	gl_FrontColor = matDiffuse;
}