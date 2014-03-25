uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform vec4 matAmbiant;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

void main(void)
{
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_Vertex;
	gl_FrontColor = matDiffuse;
}