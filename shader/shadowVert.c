#version 330

// Matrix
uniform mat4 MVP;

//Attribute
layout(location = 0) in vec3 vertexArray;
 
void main()
{
  gl_Position = MVP * vec4(vertexArray, 1.0);
}
