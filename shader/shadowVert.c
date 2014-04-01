uniform mat4 depthProjectionMatrix, depthViewMatrix, depthModelMatrix;

in vec3 vertexArray;
 
void main()
{
  gl_Position = depthProjectionMatrix * depthViewMatrix * depthModelMatrix * vec4(vertexArray, 1.0);
}
