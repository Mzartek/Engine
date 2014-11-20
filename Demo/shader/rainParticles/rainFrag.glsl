#version 440

uniform sampler2D colorTexture;

in VertexData
{
	vec2 texCoord;
} FragIn;

layout(location = 0) out vec4 fragColor;

void main(void)
{
	vec4 color = texture(colorTexture, FragIn.texCoord);

    if(color.a > 0.5)
    {
		fragColor = color;
		gl_FragDepth = gl_FragCoord.z;
    }
    else
		gl_FragDepth = 1.0;
}
