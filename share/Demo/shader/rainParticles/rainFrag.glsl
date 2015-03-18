#version 440

uniform sampler2D colorTexture;
uniform sampler2D depthTexture;

in VertexData
{
	vec2 texCoord;
} FragIn;

layout(location = 0) out vec4 outColor;

void main(void)
{
    vec4 color = texture(colorTexture, FragIn.texCoord);

	float depth = texelFetch(depthTexture, ivec2(gl_FragCoord.xy), 0).x;
	
	if (depth < gl_FragCoord.z)
		discard;
	outColor = color;
}
