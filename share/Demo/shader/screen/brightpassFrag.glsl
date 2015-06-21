#version 440

const float Luminance = 0.08f;
const float fMiddleGray = 0.18f;
const float fWhiteCutoff = 0.8f;

uniform sampler2D inputTexture;

in VertexData
{
	vec2 texCoord;
} FragIn;

layout(location = 0) out vec4 fragColor;

vec4 brightPassFilter(void)
{
	vec3 colorOut = texture(inputTexture, FragIn.texCoord).xyz;
	
	colorOut *= fMiddleGray / (Luminance + 0.001);
  colorOut *= (1.0 + (colorOut / (fWhiteCutoff * fWhiteCutoff)));
  colorOut -= 5.0;

  colorOut = max(colorOut, 0.0);

  colorOut /= (10.0 + colorOut);

  return vec4(colorOut, 1.0);
}

void main(void)
{
	fragColor = brightPassFilter();
}
