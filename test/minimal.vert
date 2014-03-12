uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
     gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_Vertex;
}
