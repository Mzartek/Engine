#version 330

uniform samplerCube cubeMap;

in vec3 outTexCoord;

void main(void)
{
  gl_FragColor = texture(cubeMap, outTexCoord);
  /* gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0); */
}
