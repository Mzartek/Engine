uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main(void)
{
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_Vertex;
}