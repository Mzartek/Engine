#version 440

uniform sampler2D colorTexture;

in VertexData
{
	vec2 texCoord;
} FragIn;

void main()
{
	float transparency = texture(colorTexture, vec2(FragIn.texCoord.x, 1.0 - FragIn.texCoord.y)).a;
	if (transparency > 0.5)
		gl_FragDepth = gl_FragCoord.z;
	else
		gl_FragDepth = 1.0;
}
