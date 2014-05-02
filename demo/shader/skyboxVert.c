#version 330

uniform mat4 MVP;
layout(location = 0) in vec3 vertexArray;

out vec3 outTexCoord;

void main(void)
{
  gl_Position = MVP * vec4(vertexArray, 1.0);
  outTexCoord = vertexArray;
}
