#version 330

// Matrix
uniform mat4 lightMatrix, modelMatrix;

//Attribute
layout(location = 0) in vec3 vertexArray;
 
void main()
{
  gl_Position = lightMatrix * modelMatrix * vec4(vertexArray, 1.0);
}
