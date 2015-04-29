#version 440

uniform sampler2D diffuseTex;

in VertexData
{
	vec2 texCoord;
} FragIn;

void main()
{
	float transparency = texture(diffuseTex, vec2(FragIn.texCoord.x, 1.0 - FragIn.texCoord.y)).w;
	if (transparency > 0.5)
		gl_FragDepth = gl_FragCoord.z;
	else
		discard;
}
