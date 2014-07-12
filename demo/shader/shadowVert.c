#version 330

uniform mat4 MVP;

out vec2 texCoord;

layout(location = 0) in vec3 vertexArray;
layout(location = 1) in vec2 textureArray;

void main()
{
  gl_Position = MVP * vec4(vertexArray, 1.0);
  texCoord = textureArray;
}
