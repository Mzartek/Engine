#version 330

// Matrix
uniform mat4 depthProjectionMatrix, depthViewMatrix, depthModelMatrix;

//Attribute
layout(location = 0) in vec3 vertexArray;
 
void main()
{
  gl_Position = depthProjectionMatrix * depthViewMatrix * depthModelMatrix * vec4(vertexArray, 1.0);
}
