#version 330

uniform sampler2D colorTexture;

in vec2 outTexCoord;
in vec4 outMatDiffuse;

out vec4 fragColor;

void main(void)
{
  fragColor = texture(colorTexture, outTexCoord) * outMatDiffuse;
}
