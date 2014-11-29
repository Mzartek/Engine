#version 440

uniform sampler2D colorTexture;

in VertexData
{
	vec2 texCoord;
} FragIn;

layout(location = 0) out vec4 outNormal;
layout(location = 1) out uvec4 outMaterial;

void main(void)
{
    vec4 color = texture(colorTexture, FragIn.texCoord);

    if(color.a > 0.5)
    {
        outNormal = vec4(0, 0, 0, 1);
		outMaterial.x = packUnorm4x8(color);
		outMaterial.y = packUnorm4x8(vec4(1, 1, 1, 1));
		outMaterial.z = packUnorm4x8(vec4(0, 0, 0, 0));
		outMaterial.w = packUnorm4x8(vec4(0, 0, 0, 0));
		gl_FragDepth = gl_FragCoord.z;
    }
    else
		gl_FragDepth = 1.0;
}
