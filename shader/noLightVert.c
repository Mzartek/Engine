#version 330

uniform mat4 projectionMatrix, viewMatrix, modelMatrix;
uniform vec4 matDiffuse;

layout(location = 0) in vec3 vertexArray;
layout(location = 1) in vec2 textureArray;
layout(location = 2) in vec3 normalArray;

out vec2 outTexCoord;
out vec4 outMatDiffuse;

void main(void)
{
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexArray, 1.0);
  outTexCoord = vec2(textureArray.x, 1.0 - textureArray.y);
  outMatDiffuse = matDiffuse;
}
